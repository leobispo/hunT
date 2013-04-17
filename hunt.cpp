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
#include "hunt.h"

#include <fstream>

HunT::HunT(size_t maxMismatch) : _maxMismatch(maxMismatch)
{
}

void HunT::addStateMachine(const StateMachine &state)
{
  _states.push_back(state);
}

void HunT::execute(const std::string &geneFile, const std::function<void(const std::string &, const std::string &,
  const std::vector<PositionToMark> &, const std::vector<HIT> &)> &callback) const
{
  std::ifstream is;

  is.open(geneFile);

  if (!is.is_open())
    throw HunTException("Problems to open the input file: " + geneFile);

  std::string geneName, geneSequence;
  while (!is.eof()) {
    std::string line;

    std::getline(is, line);
    if (!line.empty() && line.at(0) == '>') {
      if (!geneSequence.empty() && !geneSequence.empty())
        processSequence(geneName, geneSequence, callback);

      geneName = line;
      geneSequence.clear();
    }
    else
      geneSequence += line;
  }

  if (!geneSequence.empty() && !geneSequence.empty())
    processSequence(geneName, geneSequence, callback);

  is.close();
}

void HunT::processSequence(const std::string &geneName, const std::string &geneSequence, 
  const std::function<void(const std::string &, const std::string &,
  const std::vector<PositionToMark> &, const std::vector<HIT> &)> &callback) const
{
  size_t sm = 0;
  std::vector<HIT>            finalHit;
  std::vector<PositionToMark> finalMarks;

  for (auto &stateMachine : _states) {
    std::vector<HIT> hit;
    std::vector<PositionToMark> marks;
    for (size_t idx = 0; idx <= geneSequence.size() - stateMachine.size(); ++idx) {
      std::vector<PositionToMark> tmpMarks;
      size_t mismatchFound = 0;
      stateMachine.restart(); 

      for (size_t idxState = idx; idx < geneSequence.size(); ++idxState) {
        const State *currentState = stateMachine.nextState();

        if (!currentState->contains(geneSequence.at(idxState))) {
          if (currentState->acceptMismatch()) {
            tmpMarks.push_back(PositionToMark(PositionToMark::Type::MISMATCH, idxState, sm));
            ++mismatchFound;

            if (mismatchFound > _maxMismatch)
              break;
          }
          else
            break;
        }

        if (currentState->isFinalState() && idxState != geneSequence.size()) {
          marks.push_back(PositionToMark(PositionToMark::Type::BEGIN, idx, sm));
          marks.push_back(PositionToMark(PositionToMark::Type::END, idxState, sm));
          marks.insert(marks.end(), tmpMarks.begin(), tmpMarks.end());

          hit.push_back(HIT(idx, idxState, mismatchFound, stateMachine));
          break;
        }
      }
    }

    if (stateMachine.checkNumberOfPatterns(hit)) {
      finalMarks.insert(finalMarks.end(), marks.begin(), marks.end());
      finalHit.insert(finalHit.end(), hit.begin(), hit.end());
    }
    ++sm;
  }

  if (!finalHit.empty()) {
    std::sort(finalMarks.begin(), finalMarks.end(), [] (const PositionToMark &p1,
      const PositionToMark &p2) -> bool {
      if (p1.position() == p2.position())
        return p1.type() < p2.type();

      return p1.position() < p2.position();
    });

    callback(geneName, geneSequence, finalMarks, finalHit);
  }
}
