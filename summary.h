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
#ifndef SUMMARY_H
#define SUMMARY_H

#include <vector>
#include <string>
#include <fstream>

#include "hit.h"

/**
 * This class will create an HTML summary file containing information about the found patterns.
 *
 * @param Leonardo Bispo de Oliveira.
 *
 */
class Summary final
{
  public:
    /**
     * Constructor.
     *
     * @param fileName Summary file name to be created.
     *
     */
    Summary(const std::string &fileName);

    /**
     * Destructor.
     *
     */
    ~Summary();

    /**
     * Create the beginning of the HTML file.
     *
     * @param commandLine Command line passed to execute the process.
     *
     */
    void createHeader(const std::string &commandLine);

    /**
     * Append a new gene information for each sequence gene processed.
     *
     * @param geneName Processed sequence gene name.
     * @param hit A list of matches.
     *
     */
    void appendGene(const std::string &geneName, const std::vector<HIT> &hit);

    /**
     * Will finalize the HTML file.
     *
     * @pararm numberOfElements Number of sequence genes that do they have a match.
     *
     */
    void createFooter(size_t numberOfElements);

  private:
    std::ofstream _os;
};

#endif
