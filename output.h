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
#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <string>
#include <fstream>

#include "hit.h"

/**
 * This class will create an HTML output highlighting all the matches found on a sequence gene.
 *
 * @param Leonardo Bispo de Oliveira.
 *
 */
class Output final
{
  public:
    /**
     * Constructor.
     *
     * @param fileName Output file name to be created.
     *
     */
    Output(const std::string &fileName);

    /**
     * Destructor.
     *
     */
    ~Output();

    /**
     * Create the beginning of the HTML file.
     *
     */
    void createHeader();

    /**
     * Append a new gene information for each sequence gene processed.
     *
     * @param geneName Processed sequence gene name.
     * @param geneSequence Sequence of ACTG nucleotide used in the match.
     * @param positions Postions where there where a pattern match or nucleotide mismatch.
     *
     */
    void appendGene(const std::string &geneName, const std::string &geneSequence,
      const std::vector<PositionToMark> &positions);

    /**
     * Will finalize the HTML file.
     *
     */
    void createFooter();

  private:
    std::ofstream _os;

};

#endif
