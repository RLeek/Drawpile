/*
   DrawPile - a collaborative drawing program.

   Copyright (C) 2006 Calle Laakkonen

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include "user.h"
#include "layer.h"

namespace drawingboard {

User::User(int id)
	: id_(id)
{
}

/**
 * This function must be called before strokeMotion or strokeEnd.
 * @param layer the layer on which the stroke is drawn.
 * @param x initial x coordinate
 * @param y initial y coordinate
 * @param pressure initial pressure
 */
void User::strokeBegin(Layer *layer, int x, int y, qreal pressure)
{
	layer_ = layer;
	lastx_ = x;
	lasty_ = y;
	lastpressure_ = pressure;
	penmoved_ = false;
}

void User::strokeMotion(int x,int y, qreal pressure)
{
	layer_->drawLine(
			QPoint(lastx_,lasty_), lastpressure_,
			QPoint(x,y), pressure,
			brush_
			);
	lastx_ = x;
	lasty_ = y;
	lastpressure_ = pressure;
	penmoved_ = true;
}

void User::strokeEnd()
{
	if(penmoved_ == false) {
		layer_->drawPoint(QPoint(lastx_,lasty_), lastpressure_, brush_);
	}
}

}

