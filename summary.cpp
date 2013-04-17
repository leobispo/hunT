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
#include "summary.h"

Summary::Summary(const std::string &fileName)
{
  _os.open(fileName + "_summary.html");
}

Summary::~Summary()
{
  _os.close();
}

void Summary::createHeader(const std::string &commandLine)
{
  _os << "<html>" << std::endl;
  _os << "<p>" << std::endl << "<font size=2>" << std::endl;
  _os << "search-parameters:" << std::endl  << std::endl;
  _os << commandLine << std::endl;
  _os << "</font></p>" << std::endl;

  _os << "  <br>";
  _os << "  <body>" << std::endl << "    <table border=\"1\">" << std::endl;
  _os << "      <tr>" << std::endl;
  _os << "        <td>" << std::endl;
  _os << "         <h5><center> Sequence Name</center></h5>" << std::endl;
  _os << "        </td>" << std::endl;
  _os << "        <td>" << std::endl;
  _os << "         <h5><center> Hit Pattern</center></h5>" << std::endl; 
  _os << "        </td>" << std::endl;
  _os << "        <td>" << std::endl;
  _os << "         <h5><center> P_ositions</center></h5>" << std::endl; 
  _os << "        </td>" << std::endl;
  _os << "      </tr>" << std::endl;
}

void Summary::appendGene(const std::string &geneName, const std::vector<HIT> &hit)
{
  _os << "      <tr>" << std::endl;
  _os << "        <td>" << std::endl;
  _os << "          " << geneName << std::endl; 
  _os << "        </td>" << std::endl;

  _os << "        <td>" << std::endl;
  _os << "          <table border=\"1\" width=\"100%\">" << std::endl; 

  _os << "            <tr>" << std::endl;
  _os << "              <td>" << std::endl;
  _os << "                Name" << std::endl; 
  _os << "              </td>" << std::endl;
  _os << "              <td>" << std::endl;
  _os << "                Match" << std::endl; 
  _os << "              </td>" << std::endl;
  _os << "              <td>" << std::endl;
  _os << "                Mismatch" << std::endl;
  _os << "              </td>" << std::endl;
  _os << "              <td>" << std::endl;
  _os << "                Strand" << std::endl; 
  _os << "              </td>" << std::endl;
  _os << "            </tr>" << std::endl;

  for (auto &h : hit) {
    _os << "            <tr>" << std::endl;
    _os << "              <td>" << std::endl;
    _os << "                " << h.stateMachine().label() << std::endl; 
    _os << "              </td>" << std::endl;
    _os << "              <td>" << std::endl;
    _os << "                " << h.stateMachine().pattern() << std::endl; 
    _os << "              </td>" << std::endl;
    _os << "              <td>" << std::endl;
    _os << "                " << h.numberMismatches() << std::endl;
    _os << "              </td>" << std::endl;
    _os << "              <td>" << std::endl;
    _os << "                " << h.stateMachine().strand() << std::endl; 
    _os << "              </td>" << std::endl;
    _os << "            </tr>" << std::endl;
  }

  _os << "          </table>" << std::endl; 
  _os << "        </td>" << std::endl;
      
  _os << "        <td>" << std::endl;
  _os << "          <table border=\"1\" width=\"100%\">" << std::endl; 
  _os << "            <tr>" << std::endl;
  _os << "              <td>" << std::endl;
  _os << "                Start" << std::endl; 
  _os << "              </td>" << std::endl;
  _os << "              <td>" << std::endl;
  _os << "                End" << std::endl; 
  _os << "              </td>" << std::endl;
  _os << "            </tr>" << std::endl;

  for (auto &h : hit) {
    _os << "            <tr>" << std::endl;
    _os << "              <td>" << std::endl;
    _os << "                " << h.begin() << std::endl; 
    _os << "              </td>" << std::endl;
    _os << "              <td>" << std::endl;
    _os << "                " << h.end() << std::endl; 
    _os << "              </td>" << std::endl;
    _os << "            </tr>" << std::endl;
  }
  _os << "          </table>" << std::endl; 
  _os << "        </td>" << std::endl;
  _os << "      </tr>" << std::endl;
}

void Summary::createFooter(size_t numberOfElements)
{
  _os << "    </table>" << std::endl;
  _os << "<br> Number of targets sequences: " << numberOfElements << std::endl; 
  _os << " </body></html>" << std::endl;
}
