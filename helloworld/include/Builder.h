#ifndef BUILDER_H
#define BUILDER_H

#include "Machine.h"
#include "Box.h"
#include "Box2D.h"

class Builder : public Machine{
	public:
		Builder(double xo, double yo);
		void add_box(Box *b){boxlist[cur_box_idx] = b; cur_box_idx++;}
		// void Update();
		void setBody(b2Body& bod){
      body = &bod;
    }
		void Update();
		void launch(double velocity, double theta);

	private:
		double x, y;

};


#endif
