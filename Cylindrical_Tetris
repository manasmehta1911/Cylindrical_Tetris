#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <PS2X_lib.h>  //for v1.6

#define PS2_DAT 14  //MISO  19
#define PS2_CMD 12  //MOSI  23
#define PS2_SEL 13  //SS     5
#define PS2_CLK 5   //SLK   18

#define pressures false
#define rumble false

PS2X ps2x;  // create PS2 Controller Class

int error = -1;
byte type = 0;
byte vibrate = 0;
int tryNum = 1;

#ifndef PSTR
#define PSTR  // Make Arduino Due happy
#endif
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

#define GRID_H 13
#define GRID_W 30
int grid_h = GRID_H;
int grid_w = GRID_W;

#define STRAND_LENGTH GRID_W*(GRID_H + 5)
#define LED_DATA_PIN 4
// max size of each tetris piece
#define PIECE_W 3
#define PIECE_H 3
// how many kinds of pieces
#define NUM_PIECE_TYPES 7

const int arrow[5][5] = {
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 1, 0, 1, 0, 1 },
  { 0, 1, 1, 1, 0 },
  { 0, 0, 1, 0, 0 },
};

const int letters[][5][3] = { { { 0, 1, 0 },
                                { 1, 0, 1 },
                                { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 } },
                              { { 1, 1, 0 },
                                { 1, 0, 1 },
                                { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 0 } },
                              { { 1, 1, 1 },
                                { 1, 0, 0 },
                                { 1, 0, 0 },
                                { 1, 0, 0 },
                                { 1, 1, 1 } },
                              { { 1, 1, 0 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 0 } },
                              { { 1, 1, 1 },
                                { 1, 0, 0 },
                                { 1, 1, 0 },
                                { 1, 0, 0 },
                                { 1, 1, 1 } },
                              { { 1, 1, 1 },
                                { 1, 0, 0 },
                                { 1, 1, 1 },
                                { 1, 0, 0 },
                                { 1, 0, 0 } },
                              { { 1, 1, 1 },
                                { 1, 0, 0 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 } },
                              { { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 } },
                              { { 1, 1, 1 },
                                { 0, 1, 0 },
                                { 0, 1, 0 },
                                { 0, 1, 0 },
                                { 1, 1, 1 } },
                              { { 1, 1, 1 },
                                { 0, 0, 0 },
                                { 0, 1, 0 },
                                { 1, 1, 0 },
                                { 1, 1, 0 } },
                              { { 1, 0, 0 },
                                { 1, 0, 1 },
                                { 1, 1, 0 },
                                { 1, 0, 1 },
                                { 1, 0, 0 } },
                              { { 1, 0, 0 },
                                { 1, 0, 0 },
                                { 1, 0, 0 },
                                { 1, 0, 0 },
                                { 1, 1, 1 } },
                              { { 1, 0, 1 },
                                { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 } },
                              { { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 } },
                              { { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 } },
                              { { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 },
                                { 1, 0, 0 },
                                { 1, 0, 0 } },
                              { { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 },
                                { 1, 0, 1 } },
                              { { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 },
                                { 1, 1, 0 },
                                { 1, 0, 1 } },
                              { { 1, 1, 1 },
                                { 1, 0, 0 },
                                { 1, 1, 1 },
                                { 0, 0, 1 },
                                { 1, 1, 1 } },
                              { { 1, 1, 1 },
                                { 0, 1, 0 },
                                { 0, 1, 0 },
                                { 0, 1, 0 },
                                { 0, 1, 0 } },
                              { { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 } },
                              { { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 0, 1, 0 } },
                              { { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 },
                                { 1, 0, 1 } },
                              { { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 0, 1, 0 },
                                { 1, 0, 1 },
                                { 1, 0, 1 } },
                              { { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 0, 1, 0 },
                                { 0, 1, 0 },
                                { 0, 1, 0 } },
                              { { 1, 1, 1 },
                                { 0, 0, 1 },
                                { 0, 1, 0 },
                                { 1, 0, 0 },
                                { 1, 1, 1 } } };

const int numbers[][5][3] = { { { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 } },
                              { { 0, 1, 0 },
                                { 1, 1, 0 },
                                { 0, 1, 0 },
                                { 0, 1, 0 },
                                { 1, 1, 1 } },
                              { { 1, 1, 1 },
                                { 0, 0, 1 },
                                { 1, 1, 1 },
                                { 1, 0, 0 },
                                { 1, 1, 1 } },
                              { { 1, 1, 1 },
                                { 0, 0, 1 },
                                { 1, 1, 1 },
                                { 0, 0, 1 },
                                { 1, 1, 1 } },
                              { { 1, 0, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 },
                                { 0, 0, 1 },
                                { 0, 0, 1 } },
                              { { 1, 1, 1 },
                                { 1, 0, 0 },
                                { 1, 1, 1 },
                                { 0, 0, 1 },
                                { 1, 1, 1 } },
                              { { 1, 1, 1 },
                                { 1, 0, 0 },
                                { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 } },
                              { { 1, 1, 1 },
                                { 0, 0, 1 },
                                { 0, 0, 1 },
                                { 0, 0, 1 },
                                { 0, 0, 1 } },
                              { { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 } },
                              { { 1, 1, 1 },
                                { 1, 0, 1 },
                                { 1, 1, 1 },
                                { 0, 0, 1 },
                                { 1, 1, 1 } } };

const int specials[][5][3] = { {
                                 { 0, 0, 1 },
                                 { 0, 0, 1 },
                                 { 0, 1, 0 },
                                 { 1, 0, 0 },
                                 { 1, 0, 0 },
                               },
                               {
                                 { 0, 0, 0 },
                                 { 0, 1, 0 },
                                 { 0, 0, 0 },
                                 { 1, 0, 1 },
                                 { 0, 0, 0 },
                               },
                               {
                                 { 0, 0, 0 },
                                 { 1, 0, 1 },
                                 { 0, 1, 0 },
                                 { 1, 0, 1 },
                                 { 0, 0, 0 },
                               },
                               {
                                 { 0, 0, 0 },
                                 { 1, 1, 1 },
                                 { 1, 0, 1 },
                                 { 1, 1, 1 },
                                 { 0, 0, 0 },
                               } };

const int pieces[][4][3][3] = {
  { { { 1, 1, 0 },
      { 1, 1, 0 },
      { 0, 0, 0 } },

    { { 1, 1, 0 },
      { 1, 1, 0 },
      { 0, 0, 0 } },

    { { 1, 1, 0 },
      { 1, 1, 0 },
      { 0, 0, 0 } },

    { { 1, 1, 0 },
      { 1, 1, 0 },
      { 0, 0, 0 } } },
  { { { 1, 1, 0 },
      { 0, 1, 1 },
      { 0, 0, 0 } },

    { { 0, 0, 1 },
      { 0, 1, 1 },
      { 0, 1, 0 } },

    { { 0, 0, 0 },
      { 1, 1, 0 },
      { 0, 1, 1 } },

    { { 0, 1, 0 },
      { 1, 1, 0 },
      { 1, 0, 0 } } },
  { { { 0, 1, 1 },
      { 1, 1, 0 },
      { 0, 0, 0 } },

    { { 0, 1, 0 },
      { 0, 1, 1 },
      { 0, 0, 1 } },

    { { 0, 0, 0 },
      { 0, 1, 1 },
      { 1, 1, 0 } },

    { { 1, 0, 0 },
      { 1, 1, 0 },
      { 0, 1, 0 } } },
  { { { 0, 1, 0 },
      { 1, 1, 1 },
      { 0, 0, 0 } },

    { { 0, 1, 0 },
      { 0, 1, 1 },
      { 0, 1, 0 } },

    { { 0, 0, 0 },
      { 1, 1, 1 },
      { 0, 1, 0 } },

    { { 0, 1, 0 },
      { 1, 1, 0 },
      { 0, 1, 0 } } },
  { { { 1, 0, 0 },
      { 1, 0, 0 },
      { 1, 1, 0 } },

    { { 1, 1, 1 },
      { 1, 0, 0 },
      { 0, 0, 0 } },

    { { 0, 1, 1 },
      { 0, 0, 1 },
      { 0, 0, 1 } },

    { { 0, 0, 0 },
      { 0, 0, 1 },
      { 1, 1, 1 } } },
  { { { 1, 0, 0 },
      { 1, 1, 1 },
      { 0, 0, 0 } },

    { { 1, 1, 0 },
      { 1, 0, 0 },
      { 1, 0, 0 } },

    { { 1, 1, 1 },
      { 0, 0, 1 },
      { 0, 0, 0 } },

    { { 0, 0, 1 },
      { 0, 0, 1 },
      { 0, 1, 1 } } },
  { { { 0, 0, 0 },
      { 1, 1, 1 },
      { 0, 0, 0 } },

    { { 0, 1, 0 },
      { 0, 1, 0 },
      { 0, 1, 0 } },

    { { 0, 0, 0 },
      { 1, 1, 1 },
      { 0, 0, 0 } },

    { { 0, 1, 0 },
      { 0, 1, 0 },
      { 0, 1, 0 } } }
};

int piece_no = random(0, NUM_PIECE_TYPES);
int next_piece_no = random(0, NUM_PIECE_TYPES);
int rotate = 0;
int current_y = 0;
int current_x = random(0, GRID_W);
int last = 0;
int score = 0;
int pieces_count = 0;
int speed;
bool select_mode = false;
bool select_difficulty = false;
bool start = false;
bool pause = true;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRAND_LENGTH, LED_DATA_PIN, NEO_RGB + NEO_KHZ800);

int grid[GRID_H][GRID_W];
int fixed_grid[GRID_H][GRID_W];
int top_grid[5][GRID_W];

int piece_x;
int piece_y;
int piece_id;
int piece_rotation;
int timer_game_over;
int actual_speed;
bool fall_faster = false;
bool game_over = true;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(GRID_W, GRID_H, LED_DATA_PIN,
                                               NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                                               NEO_GRB + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

bool isGameOver() {
  int i = 0;
  for (i = 0; i < grid_w; i++) {
    if (fixed_grid[0][i] != -1) {
      timer_game_over = millis();

      for (int l = 0; l < GRID_H; l++) {
        for (int m = 0; m < GRID_W; m++) {
          grid[l][m] = 0;
          fixed_grid[l][m] = -1;
        }
      }
      draw_grid();
      game_over = true;
      return true;
    }
  }
  return false;
}

int x = matrix.width();
int pass = 0;
String name = "";

void gameOver() {
  matrix.fillScreen(0);
  for (int j = 0; j < 5; j++) {
    for (int k = 0; k < GRID_W; k++) {
      top_grid[j][k] = 0;
    }
  }
  print_string("SCORE" + String(score), 0, 0, top_grid);
  matrix.setCursor(x, 0);
  name = "GAME OVER";
  int len = name.length();
  matrix.print((name));
  if (--x < -(len * 6)) {
    x = matrix.width();
    if (++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();

  if (type == 1) {
    ps2x.read_gamepad(false, vibrate);
    if (ps2x.Button(PSB_START)) {
      game_over = false;
      new_game();
    }
    else if (ps2x.Button(PSB_CIRCLE)) {
      select_mode = true;
      game_over = false;
      pieces_count = 0;
      for (int j = 0; j < 5; j++) {
        for (int k = 0; k < GRID_W; k++) {
          top_grid[j][k] = 0;
        }
      }
    }
  }
  if ((millis() - timer_game_over) >= 17000) {
  }
  delay(100);
}

void p(int x, int y, long color) {
  int a = (GRID_H - 1 - y) * GRID_W;
  a += x;
  a %= GRID_H * GRID_W;
  strip.setPixelColor(a, color);
}

void q(int x, int y, long color) {
  int a = (GRID_H + 5 - 1 - y) * GRID_W;
  a += x;
  a %= STRAND_LENGTH;
  strip.setPixelColor(a, color);
}

int piece_color[][3] = { { 145, 207, 2 }, { 0, 255, 0 }, { 209, 21, 134 }, { 39, 207, 184 }, { 196, 179, 24 }, { 115, 9, 104 }, { 255, 0, 0 } };

void draw_grid() {
  int x, y;
  if (!game_over) {
    for (y = 0; y < GRID_H; ++y) {
      for (x = 0; x < GRID_W; ++x) {
        if (grid[y][x] == 1) {
          p(x, y, strip.Color(piece_color[piece_no][0], piece_color[piece_no][1], piece_color[piece_no][2]));
        } else if (fixed_grid[y][x] != -1) {
          p(x, y, strip.Color(piece_color[fixed_grid[y][x]][0], piece_color[fixed_grid[y][x]][1], piece_color[fixed_grid[y][x]][2]));
        } else {
          p(x, y, 0);
        }
      }
    }
  }
  for (int y = 0; y < 5; ++y) {
    for (int x = 0; x < GRID_W; ++x) {
      if (top_grid[y][x] == 1) {
        q(x, y, strip.Color(piece_color[next_piece_no][0], piece_color[next_piece_no][1], piece_color[next_piece_no][2]));
      } else {
        q(x, y, 0);
      }
    }
  }
  // delay(100);
}

bool check_left() {
  int temp;
  for (int i = current_x; i < current_x + 3; i++) {
    for (int j = current_y; j < current_y + 3; j++) {
      if (i == grid_w) {
        temp = 0;
      } else if (i == (grid_w + 1)) {
        temp = 1;
      } else {
        temp = i;
      }
      if ((grid[j][temp] == 1) && ((temp != 0 && fixed_grid[j][temp - 1] != -1) || (temp == 0 && fixed_grid[j][grid_w - 1] != -1))) {
        return false;
      }
    }
  }
  return true;
}

bool check_right() {
  int temp;
  for (int i = current_x; i < current_x + 3; i++) {
    for (int j = current_y; j < current_y + 3; j++) {
      if (i == grid_w) {
        temp = 0;
      } else if (i == (grid_w + 1)) {
        temp = 1;
      } else {
        temp = i;
      }
      if ((grid[j][temp] == 1) && ((temp != (grid_w - 1) && fixed_grid[j][temp + 1] != -1) || (temp == (grid_w - 1) && fixed_grid[j][0] != -1))) {
        return false;
      }
    }
  }
  return true;
}

bool check_down() {
  int temp;
  for (int i = current_y; i < current_y + 3; i++) {
    for (int j = current_x; j < current_x + 3; j++) {
      if (j == grid_w) {
        temp = 0;
      } else if (j == (grid_w + 1)) {
        temp = 1;
      } else {
        temp = j;
      }
      if ((grid[i][temp] == 1 && i == (grid_w - 1)) || ((grid[i][temp] == 1) && fixed_grid[i + 1][temp] != -1)) {
        return false;
      }
    }
  }
  return true;
}

void add_piece(int grid_matrix[GRID_H][GRID_W]) {
  int temp_x;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if ((current_x + j) == grid_w) {
        temp_x = 0;
      } else if ((current_x + j) == grid_w + 1) {
        temp_x = 1;
      } else {
        temp_x = current_x + j;
      }
      grid_matrix[current_y + i][temp_x] = pieces[piece_no][rotate][i][j];
    }
  }
}

void rotate_piece(int prev_rotate) {
  int temp_grid[GRID_H][GRID_W];

  for (int i = 0; i < grid_h; i++) {
    for (int j = 0; j < grid_w; j++) {
      temp_grid[i][j] = 0;
    }
  }

  add_piece(temp_grid);

  int flag = 0;
  for (int i = 0; i < grid_h; i++) {
    if (flag == 1) {
      break;
    }
    for (int j = 0; j < grid_w; j++) {
      if (temp_grid[i][j] == 1 && fixed_grid[i][j] != -1) {
        flag = 1;
        break;
      }
    }
  }
  if (flag == 0) {
    add_piece(grid);
  } else {
    rotate = prev_rotate;
  }
  delay(100);
}

void move_down() {
  if ((millis() - last) >= speed && !pause) {
    if (!check_down()) {
      for (int i = 0; i < grid_h; i++) {
        for (int j = 0; j < grid_w; j++) {
          if (grid[i][j] == 1) {
            fixed_grid[i][j] = piece_no;
          }
        }
      }
      current_y = 0;
    } else {
      current_y += 1;
      int temp[GRID_W];
      for (int i = grid_h - 1; i >= 0; i--) {
        for (int j = 0; j < grid_w; j++) {
          if (i == grid_h - 1) {
            temp[j] = grid[i][j];
            grid[i][j] = grid[i - 1][j];
          } else if (i == 0) {
            grid[i][j] = temp[j];
          } else {
            grid[i][j] = grid[i - 1][j];
          }
        }
      }
      last = millis();
    }
  }
}

void new_piece() {
  if (fall_faster) {
    speed = actual_speed;
    fall_faster = false;
    if(speed > 600)
      delay(800);
    else
      delay(500);
  }
  int temp;
  pieces_count += 1;
  current_x = random(0, grid_w);
  rotate = 0;
  piece_no = next_piece_no;
  for (int i = 0; i < grid_h; i++) {
    for (int j = 0; j < grid_w; j++) {
      grid[i][j] = 0;
    }
  }
  next_piece_no = random(0, NUM_PIECE_TYPES);
  add_piece(grid);
}

void delete_row(int row) {
  for (int i = 0; i < grid_w; i++) {
    fixed_grid[row][i] = -1;
  }
  for (int i = row; i > 0; i--) {
    for (int j = 0; j < grid_w; j++) {
      fixed_grid[i][j] = fixed_grid[i - 1][j];
    }
  }
  score += 10;
}

void check_row() {
  for (int i = grid_h - 1; i >= 0; i--) {
    for (int j = 0; j < grid_w; j++) {
      if (fixed_grid[i][j] == -1) {
        break;
      }
      if (j == grid_w - 1 && fixed_grid[i][j] != -1) {
        delete_row(i);
      }
    }
  }
}

int character;
bool is_number = false;
bool is_alphabet = false;

void print_string(String word, int col, int row, int grid_matrix[GRID_H][GRID_W]) {
  int col_no = col;
  for (int i = 0; i < word.length(); i++) {
    switch (word[i]) {
      case '/': character = 0; break;
      case '#': character = 3; break;
      case '^': character = 1; break;
      case '*': character = 2; break;
      default:
        if (word[i] >= 65 && word[i] <= 90) {
          is_alphabet = true;
        } else if (word[i] >= 48 && word[i] <= 57) {
          is_number = true;
        }
    }
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 3; k++) {
        if (is_alphabet)
          grid_matrix[j + row][k + col_no] = letters[word[i] - 65][j][k];
        else if (is_number)
          grid_matrix[j + row][k + col_no] = numbers[word[i] - 48][j][k];
        else
          grid_matrix[j + row][k + col_no] = specials[character][j][k];
      }
    }
    col_no = col_no + 4;
    is_number = false;
    is_alphabet = false;
  }
  draw_grid();
}

void choose_speed() {
  print_string("*1", 8, 0, grid);
  print_string("#2", 2, 6, grid);
  print_string("^3", 13, 6, grid);
  print_string("LEVELS", 1, 0, top_grid);

  if (type == 1) {
    ps2x.read_gamepad(false, vibrate);
    if (ps2x.Button(PSB_TRIANGLE)) {
      speed = 200;
      actual_speed = 200;
      pause = false;
      select_difficulty = false;
      new_game();
    } else if (ps2x.Button(PSB_SQUARE)) {
      speed = 500;
      actual_speed = 500;
      pause = false;
      select_difficulty = false;
      new_game();
    } else if (ps2x.Button(PSB_CROSS)) {
      speed = 900;
      actual_speed = 900;
      pause = false;
      select_difficulty = false;
      new_game();
    }
  }
}

void choose_mode() {
  print_string("L1", 5, 0, grid);
  print_string("1", 7, 6, grid);
  print_string("R1", GRID_W / 2 + 5, 0, grid);
  print_string("1", GRID_W / 2 + 3, 6, grid);
  print_string("/", GRID_W / 2 + 7, 7, grid);
  print_string("2", GRID_W / 2 + 11, 8, grid);
  print_string("MODE", 1, 0, top_grid);

  if (type == 1) {
    ps2x.read_gamepad(false, vibrate);
    if (ps2x.Button(PSB_L1)) {
      grid_w = GRID_W;
      select_mode = false;
      select_difficulty = true;
    } else if (ps2x.Button(PSB_R1)) {
      grid_w = GRID_W / 2;
      select_mode = false;
      select_difficulty = true;
    }
  }
  draw_grid();
}

void new_game() {
  current_y = 0;
  score = 0;
  pieces_count = 0;
  pause = false;
  for (int i = 0; i < GRID_H; i++) {
    for (int j = 0; j < GRID_W; j++) {
      fixed_grid[i][j] = -1;
      grid[i][j] = 0;
      if (grid_w == GRID_W / 2) {
        grid[i][GRID_W - 1] = 1;
        grid[i][GRID_W - 2] = 1;
        grid[i][GRID_W / 2] = 1;
        grid[i][GRID_W / 2 + 1] = 1;
      }
    }
  }
  for (int j = 0; j < 5; j++) {
    for (int k = 0; k < GRID_W; k++) {
      top_grid[j][k] = 0;
    }
  }
  delay(100);
}

void setup() {
  Serial.begin(115200);
  matrix.begin();
  strip.begin();

  strip.setBrightness(10);
  matrix.setBrightness(10);

  matrix.setTextWrap(false);
  matrix.setTextColor(colors[0]);

  for (int i = 0; i < GRID_H; i++) {
    for (int j = 0; j < GRID_W; j++) {
      fixed_grid[i][j] = -1;
      grid[i][j] = 0;
    }
  }
  while (error != 0) {
    delay(1000);  // 1 second wait
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    Serial.print("#try config ");
    Serial.println(tryNum);
    tryNum++;
  }

  Serial.println(ps2x.Analog(1), HEX);
  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println(" Unknown Controller type found ");
      break;
    case 1:
      Serial.println(" DualShock Controller found ");
      break;
    case 2:
      Serial.println(" GuitarHero Controller found ");
      break;
    case 3:
      Serial.println(" Wireless Sony DualShock Controller found ");
      break;
  }

  delay(3000);
}

void loop() {
  if (!start) {
    if (type == 1) {
      ps2x.read_gamepad(false, vibrate);
      if (ps2x.Button(PSB_START) && pause) {
        Serial.println("Start is being held");
        speed = 500;
        actual_speed = 500;
        grid_w = GRID_W;
        game_over = false;
        start = true;
      }
      else if (ps2x.Button(PSB_CIRCLE) && pause) {
        select_mode = true;
        game_over = false;
        start = true;
      }
    }
    matrix.fillScreen(0);
    matrix.setCursor(x, 2);
    String name = "START";
    int len = name.length();
    matrix.print((name));
    if (--x < -(len * 6)) {
      x = matrix.width();
      if (++pass >= 3) pass = 0;
      matrix.setTextColor(colors[pass]);
    }
    matrix.show();
    delay(100);
  }

  else if (select_mode) {
    choose_mode();
  }

  else if (select_difficulty) {
    for (int i = 0; i < GRID_H; i++) {
      for (int j = 0; j < GRID_W; j++) {
        grid[i][j] = 0;
      }
    }
    choose_speed();
  }

  else if (!isGameOver() && !game_over) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        top_grid[j][k] = arrow[j][k];
      }
    }
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        top_grid[j + 1][k + 7] = pieces[next_piece_no][0][j][k];
      }
    }
    print_string(String(pieces_count), 11, 0, top_grid);
    draw_grid();
    if (current_y == 0 && !pause) {
      new_piece();
    }
    if (type == 1) {  //DualShock Controller
      ps2x.read_gamepad(false, vibrate);
      //read controller and set large motor
      if (ps2x.Button(PSB_START) && pause) {
        Serial.println("Start is being held");
        new_game();
        return;
      }
      if (ps2x.Button(PSB_SELECT)) {
        Serial.println("Select is being held");
        if (pause == false)
          pause = true;
        else
          pause = false;
      }

      int leftRightValue1 = ps2x.Analog(PSS_LX);
      int leftRightValue2 = ps2x.Analog(PSS_RX);
      if ((ps2x.Button(PSB_PAD_RIGHT) || (abs(leftRightValue1 - 128) > 10 && leftRightValue1 > 128)) && check_right() && !pause) {
        Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
        if (current_x == grid_w - 1) {
          current_x = 0;
        } else {
          current_x += 1;
        }
        int temp;
        for (int i = 0; i < grid_h; i++) {
          for (int j = grid_w - 1; j >= 0; j--) {
            if (j == grid_w - 1) {
              temp = grid[i][j];
              grid[i][j] = grid[i][j - 1];
            } else if (j == 0) {
              grid[i][j] = temp;
            } else {
              grid[i][j] = grid[i][j - 1];
            }
          }
        }
      }

      if ((ps2x.Button(PSB_PAD_LEFT) || (abs(leftRightValue1 - 128) > 10 && leftRightValue1 < 128)) && check_left() && !pause) {
        Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
        if (current_x == 0) {
          current_x = grid_w - 1;
        } else {
          current_x -= 1;
        }

        int temp;
        for (int i = 0; i < grid_h; i++) {
          for (int j = 0; j < grid_w; j++) {
            if (j == 0) {
              temp = grid[i][j];
              grid[i][j] = grid[i][j + 1];
            } else if (j == grid_w - 1) {
              grid[i][j] = temp;
            } else {
              grid[i][j] = grid[i][j + 1];
            }
          }
        }
      }
      if (ps2x.Button(PSB_PAD_DOWN) || ps2x.Button(PSB_L3)) {
        speed = 0;
        fall_faster = true;
      }

      if ((ps2x.Button(PSB_L2) || (abs(leftRightValue2 - 128) > 10 && leftRightValue2 > 128)) && !pause && !(current_y > grid_h - 3)) {
        Serial.println("L2 pressed");
        int prev_rotate = rotate;
        if (rotate == 3) {
          rotate = 0;
        } else {
          rotate += 1;
        }
        rotate_piece(prev_rotate);
      }
      if ((ps2x.Button(PSB_R2) || (abs(leftRightValue2 - 128) > 10 && leftRightValue2 < 128)) && !pause && !(current_y > grid_h - 3)) {
        Serial.println("R2 pressed");
        int prev_rotate = rotate;
        if (rotate == 0) {
          rotate = 3;
        } else {
          rotate -= 1;
        }
        rotate_piece(prev_rotate);
      }
    }
    delay(50);

    check_row();
    draw_grid();
    move_down();
  } else {
    gameOver();
  }
  strip.show();
}
