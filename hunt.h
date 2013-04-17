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
#ifndef HUNT_H
#define HUNT_H

#include <functional>

#include "hit.h"

/**
 * Exception fired when an error happens inside the HunT class.
 *
 * @author Leonardo Bispo de Oliveira.
 *
 */
class HunTException final : public std::exception
{
  public:
    /**
     * Constructor.
     *
     * @param reason The exception reason.
     *
     */
    HunTException(const std::string &reason) : _reason(reason)
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
 * This class will execute the pattern match. It will got through all added state machines and will try to find a match in the gene sequence.
 * If a match is found it will fire a callback, telling the position where the match happened and some other useful information.
 *
 * @author Leonardo Bispo de Oliveira.
 *
 */
class HunT final
{
  public:
    /**
     * Constructor.
     *
     * @param maxMismatch Maximum supported mismatches per state machine.
     *
     */
    HunT(size_t maxMismatch);

    /**
     * Add a new state machine to be used in the match algorithm.
     *
     * @param state New state machine to be used in the match algorithm.
     *
     */
    void addStateMachine(const StateMachine &state);

    /**
     * Execute the match algorithm. It will open the file, parse it and for all the matches fire a callback, that can implement the logic to
     * store/show the found information.
     *
     * @param geneFile Gene Fasta file.
     * @param callback Callback function that will receive the processed data.
     *
     */
    void execute(const std::string &geneFile, const std::function<void(const std::string &, const std::string &,
      const std::vector<PositionToMark> &, const std::vector<HIT> &)> &callback) const;

  private:
    size_t _maxMismatch = 0;
    std::vector<StateMachine> _states;

    /**
     * Helper to process a gene sequence.
     *
     */
    void processSequence(const std::string &geneName, const std::string &geneSequence, 
      const std::function<void(const std::string &, const std::string &,
      const std::vector<PositionToMark> &, const std::vector<HIT> &)> &callback) const;
      
};

#endif
