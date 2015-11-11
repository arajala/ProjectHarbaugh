#include "Pong.hpp"

using namespace std;

bool Pong::connectPlayer1(int port) {

	sockaddr_in serv_addr;
	hostent* server;

	// Create the socket
	player_1_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (player_1_fd < 0) {
		cout << "E: Failed to create socket" << endl;
		return false;
	}

	// Populate server information
	server = gethostbyname("localhost");
	if (server == NULL) {
		cout << "E: Failed to open socket on localhost" << endl;
		return false;
	}
	bzero((char*)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port);

	// Connect
	if (connect(player_1_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		cout << "E: Failed to connect" << endl;
		return false;
	}

	return true;
}

bool Pong::connectPlayer2(int port) {

	sockaddr_in serv_addr;
	hostent* server;

	// Create the socket
	player_2_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (player_2_fd < 0) {
		cout << "E: Failed to create socket" << endl;
		return false;
	}

	// Populate server information
	server = gethostbyname("localhost");
	if (server == NULL) {
		cout << "E: Failed to open socket on localhost" << endl;
		return false;
	}
	bzero((char*)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port);

	// Connect
	if (connect(player_2_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		cout << "E: Failed to connect" << endl;
		return false;
	}

	return true;
}

void Pong::sendPlayer1Packet() {

	// Populate the connect test buffer
	char send_buf[16];
	int n_bytes;
	// char recv_buf[1];
	// send_buf[0] = 'T';
	// send_buf[1] = '1';

	// // Test connection
	// int n_bytes = write(player_1_fd, send_buf, 2);
	// if (n_bytes < 0) {
	// 	cout << "E: Failed test write, player 1 disconnected" << endl;
	// 	exit(EXIT_FAILURE);
	// }
	// n_bytes = read(player_1_fd, recv_buf, 1);
	// if (recv_buf[0] != 'P') {
	// 	cout << "E: Failed test read, player 1 disconnected" << endl;
	// 	exit(EXIT_FAILURE);
	// }

	// Prepare trimmed data
	unsigned char tr_p1_score = (unsigned char)player_1_score;
	unsigned char tr_p2_score = (unsigned char)player_2_score;
	unsigned short tr_ball_x = (unsigned short)ball_x_position;
	unsigned short tr_ball_y = (unsigned short)ball_y_position;
	unsigned short tr_p1_pos = (unsigned short)player_1_position;
	unsigned short tr_p2_pos = (unsigned short)player_2_position;
	unsigned char tr_p1_hit = (unsigned char)player_1_paddle_hit;
	player_1_paddle_hit = false;

	// Populate the data buffer
	send_buf[0] = (char)tr_p1_score;
	send_buf[1] = (char)tr_p2_score;
	send_buf[2] = (char)(tr_ball_x & 0xFF);
	send_buf[3] = (char)((tr_ball_x >> 8) & 0xFF);
	send_buf[4] = (char)(tr_ball_y & 0xFF);
	send_buf[5] = (char)((tr_ball_y >> 8) & 0xFF);
	send_buf[6] = (char)(tr_p1_pos & 0xFF);
	send_buf[7] = (char)((tr_p1_pos >> 8) & 0xFF);
	send_buf[8] = (char)(tr_p2_pos & 0xFF);
	send_buf[9] = (char)((tr_p2_pos >> 8) & 0xFF);
	send_buf[10] = (char)(tr_p1_hit);
	send_buf[11] = (char)1;

	// Send the data
	n_bytes = write(player_1_fd, send_buf, strlen(send_buf));
	if (n_bytes < 0) {
		cout << "E: Failed data write, player 1 disconnected" << endl;
		exit(EXIT_FAILURE);
	}
}

void Pong::sendPlayer2Packet() {

	// Populate the connect test buffer
	char send_buf[16];
	int n_bytes;
	// char recv_buf[1];
	// send_buf[0] = 'T';
	// send_buf[1] = '2';

	// // Test connection
	// int n_bytes = write(player_2_fd, send_buf, 2);
	// if (n_bytes < 0) {
	// 	cout << "E: Failed test write, player 2 disconnected" << endl;
	// 	exit(EXIT_FAILURE);
	// }
	// n_bytes = read(player_2_fd, recv_buf, 1);
	// if (recv_buf[0] != 'P') {
	// 	cout << "E: Failed test read, player 2 disconnected" << endl;
	// 	exit(EXIT_FAILURE);
	// }

	// Prepare trimmed data
	unsigned char tr_p1_score = (unsigned char)player_1_score;
	unsigned char tr_p2_score = (unsigned char)player_2_score;
	unsigned short tr_ball_x = (unsigned short)ball_x_position;
	unsigned short tr_ball_y = (unsigned short)ball_y_position;
	unsigned short tr_p1_pos = (unsigned short)player_1_position;
	unsigned short tr_p2_pos = (unsigned short)player_2_position;
	unsigned char tr_p2_hit = (unsigned char)player_2_paddle_hit;
	player_2_paddle_hit = false;

	// Populate the data buffer
	send_buf[0] = (char)tr_p1_score;
	send_buf[1] = (char)tr_p2_score;
	send_buf[2] = (char)(tr_ball_x & 0xFF);
	send_buf[3] = (char)((tr_ball_x >> 8) & 0xFF);
	send_buf[4] = (char)(tr_ball_y & 0xFF);
	send_buf[5] = (char)((tr_ball_y >> 8) & 0xFF);
	send_buf[6] = (char)(tr_p1_pos & 0xFF);
	send_buf[7] = (char)((tr_p1_pos >> 8) & 0xFF);
	send_buf[8] = (char)(tr_p2_pos & 0xFF);
	send_buf[9] = (char)((tr_p2_pos >> 8) & 0xFF);
	send_buf[10] = (char)(tr_p2_hit);
	send_buf[11] = (char)2;

	// Send the data
	n_bytes = write(player_2_fd, send_buf, strlen(send_buf));
	if (n_bytes < 0) {
		cout << "E: Failed data write, player 2 disconnected" << endl;
		exit(EXIT_FAILURE);
	}
}

void Pong::update() {

	static bool first_move = true;
	static double ball_angle = 0.0;
	int new_x, new_y;

	// Initialize the angle on start
	if (first_move) {
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<> dis(-45.0, 45.0);
		ball_angle = dis(gen);
		ball_x_position = (int)((double)BOARD_WIDTH / 2.0);
	}

	// Calculate a new position
	new_x = (int)((double)ball_x_position + (double)BALL_SPEED * (double)cos(ball_angle));
	new_y = (int)((double)ball_y_position + (double)BALL_SPEED * (double)sin(ball_angle));

	// Check new position for bounces
	int y_diff = 0;
	if (new_y < 0) {
		y_diff = 0 - new_y;
		new_y = 0 + y_diff;
		ball_angle = -1.0 * ball_angle;
	} else if (new_y >= BOARD_HEIGHT) {
		y_diff = new_y - BOARD_HEIGHT;
		new_y = BOARD_HEIGHT - y_diff;
		ball_angle = -1.0 * ball_angle;
	}

	// Check new position for scores
	if (new_x < 0) {
		if ((new_y >= player_1_position - PADDLE_RADIUS) &&
			(new_y <= player_1_position + PADDLE_RADIUS)) {
			if (ball_angle > 0.0) {
				double axis_diff = ball_angle - 90.0;
				ball_angle = 90.0 - axis_diff;
			} else {
				double axis_diff = -ball_angle - 90.0;
				ball_angle = -90.0 + axis_diff;
			}
			int x_diff = 0 - new_x;
			new_x = 0 + x_diff;
			player_1_paddle_hit = true;
		} else {
			first_move = true;
			player_2_score += 1;
			new_x = BOARD_WIDTH / 2.0;
			new_y = BOARD_HEIGHT / 2.0;
			cout << endl;
			cout << "Player 1: " << player_1_score << endl;
			cout << "Player 2: " << player_2_score << endl;
		}
	} else if (new_x >= BOARD_WIDTH) {
		if ((new_y >= player_2_position - PADDLE_RADIUS) &&
			(new_y <= player_2_position + PADDLE_RADIUS)) {
			if (ball_angle > 0.0) {
				double axis_diff = 90.0 - ball_angle;
				ball_angle = 90.0 + axis_diff;
			} else {
				double axis_diff = -90.0 - ball_angle;
				ball_angle = -90.0 + axis_diff;
			}
			int x_diff = new_x - BOARD_WIDTH;
			new_x = BOARD_WIDTH - x_diff;
			player_2_paddle_hit = true;
		} else {
			first_move = true;
			player_1_score += 1;
			new_x = BOARD_WIDTH / 2.0;
			new_y = BOARD_HEIGHT / 2.0;
			cout << "Player 1: " << player_1_score << endl;
			cout << "Player 2: " << player_2_score << endl;
		}
	}

	// Update new position
	ball_x_position = new_x;
	ball_y_position = new_y;
}

bool Pong::isFinished() {
	return (player_1_score >= FINAL_SCORE) || (player_2_score >= FINAL_SCORE);
}

void* Pong::listenToPlayer1(void* arg) {

	unsigned char recv_buf[16];
	int n_bytes;
	pthread_mutex_init(&lock, NULL);

	while (player_1_fd) {
		n_bytes = read(player_1_fd, recv_buf, 16);
		if (n_bytes < 1) {
			cout << "E: Did not receive data from player 1" << endl;
			exit(EXIT_FAILURE);
		}
		if (recv_buf[0] == MOVE_UP) {
			if (player_1_position < BOARD_HEIGHT-1) {
				++player_1_position;
			}
		} else if (recv_buf[0] == MOVE_DOWN) {
			if (player_1_position > 0) {
				--player_1_position;
			}
		}
		recv_buf[0] = MOVE_NOWHERE;
	}

	return NULL;
}

void* Pong::listenToPlayer2(void* arg) {

	unsigned char recv_buf[16];
	int n_bytes;

	while (player_2_fd) {
		n_bytes = read(player_2_fd, recv_buf, 16);
		if (n_bytes < 1) {
			cout << "E: Did not receive data from player 2" << endl;
			exit(EXIT_FAILURE);
		}
		if (recv_buf[0] == MOVE_UP) {
			if (player_2_position < BOARD_HEIGHT-1) {
				++player_2_position;
			}
		} else if (recv_buf[0] == MOVE_DOWN) {
			if (player_2_position > 0) {
				--player_2_position;
			}
		}
		recv_buf[0] = MOVE_NOWHERE;
	}

	return NULL;
}

int main(int argc, char** argv) {

	// Check input
	if (argc != 3) {
		cout << "E: Must specify player 1 port and player 2 port" << endl;
		exit(EXIT_FAILURE);
	}
	int player_1_port = atoi(argv[1]);
	int player_2_port = atoi(argv[2]);

	// Create pong game
	Pong game;

	// Connect player 1
	if (!game.connectPlayer1(player_1_port)) {
		cout << "E: Failed to connect to player 1 on port " << player_1_port << endl;
		exit(EXIT_FAILURE);
	}
	cout << "PLAYER 1 CONNECTED" << endl;

	// Connect player 2
	if (!game.connectPlayer2(player_2_port)) {
		cout << "E: Failed to connect to player 2 on port " << player_2_port << endl;
		exit(EXIT_FAILURE);
	}
	cout << "PLAYER 2 CONNECTED" << endl;

	// Start listening for player inputs
	pthread_t player_1_listen, player_2_listen;
	pthread_create(&player_1_listen, NULL, &Pong::listenToPlayer1, NULL);
	pthread_create(&player_2_listen, NULL, &Pong::listenToPlayer2, NULL);

	// Start the game
	cout << "GAME STARTING IN 3 SECONDS" << endl;
	usleep(3000000);
	while (!game.isFinished()) {
		game.update();
		game.sendPlayer1Packet();
		game.sendPlayer2Packet();
		usleep(1000);
	}

	cout << "GAME OVER" << endl;

	return 0;
}
