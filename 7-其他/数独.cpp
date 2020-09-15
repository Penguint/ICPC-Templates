#include<bits/stdc++.h>
using namespace std;

struct board {
  
    // Contains a 9-bit mask per square, indicating possible digits in each square
    uint16_t squares[9][9];

    // For each "unit" (rows, cols, blocks) and each digit (0..8), store a bit mask
    // indicating where this digit is still possible. This could be reconstructed from
    // the squares array above, but it's faster to maintain a redundant "reverse index".
    uint16_t possible_digit_locations_blocks[3][3][9];
    uint16_t possible_digit_locations_rows[9][9];
    uint16_t possible_digit_locations_cols[9][9];

    board() {
        std::fill_n((uint16_t*)squares, 81, (uint16_t)0x1ff);
        std::fill_n((uint16_t*)possible_digit_locations_rows, 9 * 9, (uint16_t)0x1FF);
        std::fill_n((uint16_t*)possible_digit_locations_cols, 9 * 9, (uint16_t)0x1FF);
        std::fill_n((uint16_t*)possible_digit_locations_blocks, 9 * 9, (uint16_t)0x1FF);
    }

    //.... methods go here ...
    #define FOREACH_SET_BIT(digit_mask_input, body) { \
    unsigned long bit_index; uint16_t digit_mask = (digit_mask_input); \
    while (_BitScanForward(&bit_index, digit_mask)) { \
        digit_mask &= digit_mask-1; body\
    }\
    }


    bool eliminate(int x, int y, uint16_t digits_to_eliminate) {    
        digits_to_eliminate &= squares[x][y]; // Only eliminate digits that exists in square

        if (digits_to_eliminate == 0) {
            return true; // already eliminated.
        }

        squares[x][y] &= ~digits_to_eliminate; // clear digit

        uint16_t remaining_digits = squares[x][y];

        if ( __popcnt16(remaining_digits) == 0) {
            return false; // contradiction found, no possible digits left.
        }

        int block_x = x / 3;
        int block_y = y / 3;
        int block_bit_index = (x%3) + 3*(y%3);

        // Clear out the "reverse index" 
        FOREACH_SET_BIT(digits_to_eliminate, 
            assert(possible_digit_locations_cols[x][bit_index] & (1 << y));
            possible_digit_locations_cols[x][bit_index] &= ~(1 << y);

            assert(possible_digit_locations_rows[y][bit_index] & (1 << x));
            possible_digit_locations_rows[y][bit_index] &= ~(1 << x);

            assert(possible_digit_locations_blocks[block_x][block_y][bit_index] & (1 << block_bit_index));
            possible_digit_locations_blocks[block_x][block_y][bit_index] &= ~(1 << block_bit_index);
        );  

        // If we've eliminated all but one digit, then we should eliminate that digit from all the peers.
        if (__popcnt16(remaining_digits) == 1) {
            int remaining_digit_index = get_set_bit(remaining_digits);

            // Get all the positions where this digit is set in the current row, column and block,
            // and eliminate them from those squares.
            
            // Start with the current row.
            uint16_t remaining_pos_mask = possible_digit_locations_rows[y][remaining_digit_index];
            remaining_pos_mask &= ~(1 << x); // Don't eliminate from the current square.
            FOREACH_SET_BIT(remaining_pos_mask,       
                if (!eliminate(bit_index,y, remaining_digits)) {
                    return false;
                }
            )

            // Next eliminate it from the column.
            remaining_pos_mask = possible_digit_locations_cols[x][remaining_digit_index];
            remaining_pos_mask &= ~(1 << y); // Don't eliminate from the current square
            FOREACH_SET_BIT(remaining_pos_mask,
                if (!eliminate(x, bit_index, remaining_digits)) {
                    return false;
                }
            )

            // Next eliminate it from the current block
            remaining_pos_mask = possible_digit_locations_blocks[block_x][block_y][remaining_digit_index];
            remaining_pos_mask &= ~(1 << block_bit_index); // Don't eliminate from the current square
            FOREACH_SET_BIT(remaining_pos_mask,
                int x_offset = bit_index % 3;
                int y_offset = bit_index / 3;
                if (!eliminate(block_x*3 + x_offset, block_y *3 + y_offset, remaining_digits)) {
                    return false;
                }
            )
        }

        // For each digit we just eliminated, find if it now only has one remaining posible location
        // in either the row, column or block. If so, set the digit
        FOREACH_SET_BIT(digits_to_eliminate,
            // Check the row
            if (__popcnt16(possible_digit_locations_rows[y][bit_index]) == 1) {
                int digit_x = get_set_bit(possible_digit_locations_rows[y][bit_index]);
                if (!set_digit(digit_x, y, bit_index)) {
                    return false;
                }
            }

            // Column
            if (__popcnt16(possible_digit_locations_cols[x][bit_index]) == 1) {
                int digit_y = get_set_bit(possible_digit_locations_cols[x][bit_index]);
                if (!set_digit(x, digit_y, bit_index)) {
                    return false;
                }
            }

            // Block
            if (__popcnt16(possible_digit_locations_blocks[block_x][block_y][bit_index]) == 1) {
                int bit_with_digit = get_set_bit(possible_digit_locations_blocks[block_x][block_y][bit_index]);
                int x_offset = bit_with_digit % 3;
                int y_offset = bit_with_digit / 3;
                if (!set_digit(block_x*3 + x_offset, block_y *3 + y_offset, bit_index)) {
                    return false;
                }
            }
        )
        return true; // Successfully eliminated the digits
    }

    bool set_digit(int x, int y, int d) {
        int digit_mask = 1 << d;
        assert(squares[x][y] & digit_mask);

        if (!eliminate(x, y, ~digit_mask)) {
            return false;
        }

        assert(squares[x][y] == digit_mask);
        return true;
    }

    bool search(const board& current_board, board& final_board) {
    // Find the next square to do a trial assignment on
    int x, y;
    if (current_board.find_next_square_to_assign(x, y)) {
        uint16_t digits = current_board.squares[x][y];

        // Then assign each possible digit to this square
        FOREACH_SET_BIT(digits, {
        board board_copy = current_board;
        // If we can successfully set this digit, do search from here
        if (board_copy.set_digit(x, y, bit_index)) {
            if (search(board_copy, final_board)) {
            return true;
            }
        }
        })
    }
    else {
        // No more squares to assign, so we're done!    
        assert(current_board.is_solved());
        final_board = current_board;
        return true;
    }
    return false;
    }

}

int main() {

}