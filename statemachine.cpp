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
#include "statemachine.h"

#include "hit.h"

State::State(const std::string &pattern, bool mismatch) : _pattern(pattern), _mismatch(mismatch)
{
}

State::State(const State &obj)
{
  _pattern    = obj._pattern;
  _mismatch   = obj._mismatch;
  _finalState = obj._finalState;
}

void State::setFinalState()
{
  _finalState = true;
}

bool State::contains(char nucleotide) const
{
  return _pattern.find(nucleotide, 0) != std::string::npos;
}

bool State::acceptMismatch() const
{
  return _mismatch;
}

bool State::isFinalState() const
{
  return _finalState;
}

State &State::operator=(const State &obj)
{
  _pattern    = obj._pattern;
  _mismatch   = obj._mismatch;
  _finalState = obj._finalState;

  return *this;
}

StateMachine::StateMachine(const std::string &label, const std::string &pattern, uint16_t minNumberOfPatterns, char strand) : _label(label),
  _pattern(pattern), _minNumberOfPatterns(minNumberOfPatterns), _strand(strand)
{
  std::string currentNucleotides;

  bool hasParenthesis = false;
  bool hasBrackets    = false;
  for (auto &nucleotide : pattern) {
    switch (nucleotide) {
      case 'A':
      case 'C':
      case 'T':
      case 'G':
        currentNucleotides += nucleotide;
        if (!hasBrackets) {
          _states.push_back(State(currentNucleotides, !hasParenthesis));
          currentNucleotides.clear();
        }
      break;
      case 'N':
        _states.push_back(State("ACTG", !hasParenthesis));
        currentNucleotides.clear();
      break;
      case '(':
        if (hasBrackets)
          throw ParseException("Cannot have parenthesis inside brackets");

        if (hasParenthesis)
          throw std::exception();

        hasParenthesis = true;
      break;
      case '[':
        if (hasBrackets)
          throw ParseException("Cannot have brackets inside brackets");

        hasBrackets = true;
      break;
      case ']':
        if (!hasBrackets)
          throw ParseException("Closing brackets without opening");

        if (currentNucleotides.empty())
          throw ParseException("Not enough elements inside the brackets");

        _states.push_back(State(currentNucleotides, !hasParenthesis));
        currentNucleotides.clear();
        hasBrackets = false;
      break;
      case ')':
        if (!hasParenthesis)
          throw ParseException("Closing parenthesis without opening"); 

        hasParenthesis = false;
      break;
      default:
        throw ParseException("Invalid token");
    }
  }

  if (!_states.empty())
    _states.back().setFinalState();
}

StateMachine::StateMachine(const StateMachine &obj)
{
  _pattern             = obj._pattern;
  _label               = obj._label;
  _strand              = obj._strand;
  _states              = obj._states;
  _minNumberOfPatterns = obj._minNumberOfPatterns;
}

void StateMachine::restart() const
{
  if (!_states.empty())
    _currState = 0;
  else
    _currState = -1;
}

bool StateMachine::checkNumberOfPatterns(const std::vector<HIT> &hit) const
{
  return hit.size() >= _minNumberOfPatterns;
}

const State *StateMachine::nextState() const
{
  const State *ret = nullptr;
  if (_states.size() > _currState && _currState != -1) {
    ret = &_states.at(_currState);
    ++_currState;
  }

  return ret;
}

size_t StateMachine::size() const
{
  return _states.size();
}

const std::string &StateMachine::label() const
{
  return _label;
}

const std::string &StateMachine::pattern() const
{
  return _pattern;
}

char StateMachine::strand() const
{
  return _strand;
}

StateMachine &StateMachine::operator=(const StateMachine &obj)
{
  _pattern             = obj._pattern;
  _label               = obj._label;
  _strand              = obj._strand;
  _states              = obj._states;
  _minNumberOfPatterns = obj._minNumberOfPatterns;
  return *this;
}
