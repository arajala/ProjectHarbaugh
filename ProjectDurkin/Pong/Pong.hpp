#ifndef PONG_HPP
#define PONG_HPP

#define BOARD_HEIGHT	256
#define BOARD_WIDTH		512
#define PADDLE_RADIUS	10
#define BALL_RADIUS		2
#define BALL_SPEED		5
#define FINAL_SCORE		10
#define MOVE_UP			7
#define MOVE_DOWN		8
#define MOVE_NOWHERE	9

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <random>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

class Pong {

public:

	bool connectPlayer1(int port);

	bool connectPlayer2(int port);

	void sendPlayer1Packet();

	void sendPlayer2Packet();

	void update();

	bool isFinished();

	void* listenToPlayer1(void* arg);

	void* listenToPlayer2(void* arg);

private:

	int player_1_fd;
	int player_2_fd;

	int ball_x_position;
	int ball_y_position;

	int player_1_position;
	int player_2_position;

	int player_1_score;
	int player_2_score;

	bool player_1_paddle_hit;
	bool player_2_paddle_hit;

	pthread_mutex_t lock;

};

#endif
