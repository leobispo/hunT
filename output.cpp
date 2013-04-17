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
#include "output.h"

Output::Output(const std::string &fileName)
{
  _os.open(fileName + ".html");
}

Output::~Output()
{
  _os.close();
}

void Output::createHeader()
{
  _os << "<html>" << std::endl;
  _os << "  <style type=\"text/css\">" << std::endl;
  _os << "    .pattern0 { color: darkblue; font-weight:bold; }\n" << std::endl;
  _os << "    .pattern1 { color: lightblue; font-weight:bold; }\n" << std::endl;
  _os << "    .pattern2 { color: darkgreen; font-weight:bold; }\n" << std::endl;
  _os << "    .pattern3 { color: lightgreen; font-weight:bold; }\n" << std::endl;
  _os << "    .pattern4 { color: darkred; font-weight:bold; }\n" << std::endl;
  _os << "    .pattern5 { color: lightred; font-weight:bold; }\n" << std::endl;
  _os << "    .pattern6 { color: darkbrown; font-weight:bold; }\n" << std::endl;
  _os << "    .pattern7 { color: lightbrown; font-weight:bold; }" << std::endl;
  _os << "    .gene {width:800px; word-wrap: break-word;}" << std::endl;
  _os << "  </style>" << std::endl;
  _os << "  <body>" << std::endl;
} 

void Output::appendGene(const std::string &geneName, const std::string &geneSequence,
  const std::vector<PositionToMark> &positions)
{
  _os << "    <div class=\"gene\">" << std::endl;
  _os << "      <pre>" << geneName << std::endl;
  size_t currPosition = 0;
  for (size_t i = 0; i < geneSequence.size(); ++i) {
    while (currPosition < positions.size() && positions.at(currPosition).position() == i) {
      if (positions.at(currPosition).type() == PositionToMark::Type::BEGIN)
        _os << "<span class=\"pattern" << positions.at(currPosition).patternUsed() << "\">";
      else if (positions.at(currPosition).type() == PositionToMark::Type::MISMATCH) {
        _os << "<u>";
        break;
      }
      else
        break;

      ++currPosition;
    }
    _os << geneSequence.at(i);

    while (currPosition < positions.size() && positions.at(currPosition).position() == i) {
      if (positions.at(currPosition).type() == PositionToMark::Type::MISMATCH)
        _os << "</u>";
      else if (positions.at(currPosition).type() == PositionToMark::Type::END)
        _os << "</span>";
      else
        break;

      ++currPosition;
    }
  }
  _os << std::endl << "      </pre>" << std::endl << "    </div>" << std::endl;
}

void Output::createFooter()
{
  _os << "  </body>" << std::endl << "</html>" << std::endl;
}
