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
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <string>
#include <vector>
#include <exception>

class HIT;

/**
 * Exception fired when an error happens inside the State Machine parser algorithm.
 *
 * @author Leonardo Bispo de Oliveira.
 *
 */
class ParseException final : public std::exception
{
  public:
    /**
     * Constructor.
     *
     * @param reason The exception reason.
     *
     */
    ParseException(const std::string &reason) : _reason(reason)
    {
    }

    /**
     * Returns the exception reason.
     *
     * @return The exception reason.
     *
     */
    const char *what() const _NOEXCEPT
    {
      return _reason.c_str();
    }

  private:
    std::string _reason;
};

/**
 * A state represation of a state machine entry.
 *
 * @author Leonardo Bispo de Oliveira.
 *
 */
class State final
{
  public:
    /**
     * Constructor.
     *
     * @param pattern The pattern to be match for this state.
     * @param mismatch Tell to the state machine executor if this pattern can be invalid.
     *
     */
    State(const std::string &pattern, bool mismatch);

    /**
     * Copy constructor.
     *
     * @param obj Object to be copied.
     *
     */
    State(const State &obj);

    /**
     * Returns true if this state contains a nucleotide.
     *
     * @return True if it contains a nucleotide, otherwise false.
     *
     */
    bool contains(char nucleotide) const;

    /**
     * Returns if this state accept mismatches.
     *
     * @return True if it accept mismatches, otherwise false.
     *
     */
    bool acceptMismatch() const;

    /**
     * Toggle the state to be a final state.
     *
     */
    void setFinalState();

    /**
     * Returns if the state is a final state.
     *
     * @return True if it is a final state, otherwise false.
     *
     */
    bool isFinalState() const;

    /**
     * Attribute operator.
     *
     * @param obje Object to be copied.
     *
     * @return Reference to this object.
     *
     */
    State &operator=(const State &obj);

  private:
    std::string _pattern;
    bool        _mismatch;
    bool        _finalState = false;
};

/**
 * This is a state machine class that supports the ACGT nucleotides and also some OR, and protection mechanisms to
 * looking for a pattern matches inside a gene sequence.
 *
 * @author Leonardo Bispo de Oliveira.
 *
 */
class StateMachine final
{
  public:
    /**
     * Constructor.
     *
     * This constructor will parse a pattern and create 1 state for each nucleotide in this pattern. If the pattern fails,
     * a ParserException will be fired.
     *
     * @param label A name identification.
     * @param pattern The state machine pattern.
     * @param minNumberOfPatterns Minimum number of patterns that must match to be considered a gene sequence found.
     * @param strand For which strand (normal or complement) this pattern is for.
     *
     */
    StateMachine(const std::string &label, const std::string &pattern, uint16_t minNumberOfPatterns, char strand);

    /**
     * Copy constructor.
     *
     * @param obj Object to be copied.
     *
     */
    StateMachine(const StateMachine &obj);

    /**
     * Restart the state machine to the initial state.
     *
     */
    void restart() const;

    /**
     * Return the current state and forward the state machine to the next one.
     *
     * @return Current state.
     *
     */
    const State *nextState() const;

    /**
     * Check if the number of found matches are the minimum required for this state machine.
     *
     * @param hit A hit vector to check if the size is great equal than the minimum number of patterns.
     *
     * @return True if number of hits are great equal than the minimum number of patterns.
     *
     */
    bool checkNumberOfPatterns(const std::vector<HIT> &hit) const;

    /**
     * Returns the number of states in this state machine.
     *
     * @return Number of states in this state machine.
     *
     */
    size_t size() const;

    /**
     * Returns the name identification of this state machine.
     *
     * @return The name identification of this state machine.
     *
     */
    const std::string &label() const;

    /**
     * Returns the state machine pattern.
     *
     * @return The state machine pattern.
     *
     */
    const std::string &pattern() const;

    /**
     * Returns the strand that this pattern is related.
     *
     * @return The strand that this pattern is related.
     *
     */
    char strand() const;

    /**
     * Attribute operator.
     *
     * @param obje Object to be copied.
     *
     * @return Reference to this object.
     *
     */
    StateMachine &operator=(const StateMachine &obj);

  private:
    std::string _label;
    std::string _pattern;
    char        _strand;
    uint16_t    _minNumberOfPatterns;

    std::vector<State> _states;
    mutable int        _currState = -1;
};

#endif
