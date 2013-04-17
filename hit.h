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
#ifndef HIT_H
#define HIT_H

#include "statemachine.h"

/**
 * This class will be used to store the position where a match is beginning and ending and
 * the mismatches as well. It will be used by writers to highlight the gene sequence.
 *
 * @author Leonardo Bispo de Oliveira.
 *
 */
class PositionToMark final
{
  public:
    enum class Type { BEGIN, END, MISMATCH };

    /**
     * Constructor.
     *
     * @param type The type of the mark.
     * @param position Position where this mark must be set.
     * @param patternUsed This is a pattern id to differentiate each mark.
     *
     */
    PositionToMark(Type type, size_t position, size_t patternUsed);

    /**
     * Returns the type of the mark.
     *
     * @return The type of the mark.
     *
     */
    Type type() const;

    /**
     * Returns the position where this mark must be set.
     *
     * @return The position where this mark must be set.
     *
     */
    size_t position() const;

    /**
     * Returns the pattern ID.
     *
     * @return The pattern id.
     *
     */
    size_t patternUsed() const;

  private:
    Type   _type;
    size_t _position;
    size_t _patternUsed;
};

/**
 * This class will store information about the sequence gene match.
 *
 * @author Leonardo Bispo de Oliveira.
 *
 */ 
class HIT final
{
  public:
    /**
     * Constructor.
     *
     * @param begin Position where the match is beginning.
     * @param end Position where the match is ending.
     * @param numberMismatches Number of mismatches happened on this match.
     * @param stateMachine The state machine used on this matching.
     *
     */
    HIT(size_t begin, size_t end, size_t numberMismatches, const StateMachine &stateMachine);

    /**
     * Copy constructor.
     *
     * @param obj Object to be copied.
     *
     */
    HIT(const HIT &obj);

    /**
     * Returns the position where the match is beginning.
     *
     * @return Position where the match is beginning.
     *
     */
    size_t begin() const;

    /**
     * Returns the position where the match is ending.
     *
     * @return Position where the match is ending.
     *
     */
    size_t end() const;
    /**
     * Returns the number of mismatches happened on this match.
     *
     * @return Number of mismatches happened on this match.
     *
     */
    size_t numberMismatches() const;

    /**
     * Returns the state machine used on this matching. 
     *
     * @return State machine used on this matching.
     *
     */
    const StateMachine &stateMachine() const;

    /**
     * Attribute operator.
     *
     * @param obje Object to be copied.
     *
     * @return Reference to this object.
     *
     */
    HIT &operator=(const HIT &obj);

  private:
    size_t       _begin;
    size_t       _end;
    size_t       _numberMismatches;
    StateMachine _stateMachine; 
};

#endif
