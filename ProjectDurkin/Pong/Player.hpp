#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <cairo.h>
#include <gtk/gtk.h>

#define PADDLE_HEIGHT	10
#define PADDLE_WIDTH	2
#define BALL_RADIUS		2
#define FINAL_SCORE		10
#define MOVE_UP			7
#define MOVE_DOWN		8
#define MOVE_NOWHERE	9

class Player {

public:

	void* run(void* arg);

	void* listen(void* arg);

	void setPort(int port);

	int getPlayer1Position();

	int getPlayer2Position();

	int getBallXPosition();

	int getBallYPosition();

private:

	int listen_port;

	int ball_x_position;
	int ball_y_position;

	int player_1_position;
	int player_2_position;

	int player_1_score;
	int player_2_score;

	pthread_mutex_t lock;

	void receiveDataMessage(unsigned char* buf);

};

#endif
