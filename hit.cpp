/* Copyright (C) 2013 Leonardo Bispo de Oliveira
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include "hit.h"

PositionToMark::PositionToMark(Type type, size_t position, size_t patternUsed) : _type(type), _position(position), _patternUsed(patternUsed)
{
}

PositionToMark::Type PositionToMark::type() const
{
  return _type;
}

size_t PositionToMark::position() const
{
  return _position;
}

size_t PositionToMark::patternUsed() const
{
  return _patternUsed;
}

HIT::HIT(size_t begin, size_t end, size_t numberMismatches, const StateMachine &stateMachine) : _begin(begin),
  _end(end), _numberMismatches(numberMismatches), _stateMachine(stateMachine)
{
}

HIT::HIT(const HIT &obj) : _begin(obj._begin), _end(obj._end), _numberMismatches(obj._numberMismatches), _stateMachine(obj._stateMachine)
{
}

size_t HIT::begin() const
{
  return _begin;
}

size_t HIT::end() const
{
  return _end;
}

const StateMachine &HIT::stateMachine() const
{
  return _stateMachine;
}

HIT &HIT::operator=(const HIT &obj)
{
  _begin            = obj._begin;
  _end              = obj._end;
  _stateMachine     = obj._stateMachine;
  _numberMismatches = obj._numberMismatches;
  return *this;
}

size_t HIT::numberMismatches() const
{
  return _numberMismatches;
}
