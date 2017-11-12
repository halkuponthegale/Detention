#ifndef BUILDER_H
#define BUILDER_H

#include "Machine.h"
#include "Box.h"

class Builder : public Machine{
	public:
		Builder();
		void add_box(Box *b){boxlist[cur_box_idx] = b; cur_box_idx++;}
		// void Update();


	private:


};


#endif