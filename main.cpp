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
#include <iostream>
#include <getopt.h>

#include <fstream>

#include "hunt.h"
#include "output.h"
#include "summary.h"

static
void printUsage(const char * const appName)
{
  std::cerr << "Usage " << appName << " [ARGS]" << std::endl;
  std::cerr << "\t--input-file=<file_name>" << std::endl;
  std::cerr <<  "\t--output-file=<file_name>" << std::endl;
  std::cerr << "\t--search-type=[0|1]" << std::endl;
  std::cerr << "\t--pattern=<search_pattern>" << std::endl;
  std::cerr << "\t--mismatch=[0..n]" << std::endl;
  std::cerr << "\t--pattern-min=[0..n]" << std::endl;
  std::cerr << "\t--label=<label>" << std::endl;

  exit(1);
}

static
std::string createComplement(const std::string &pattern)
{
  std::string ret;
  for (size_t i = pattern.size(); i > 0; --i) {
    char ch = pattern.at(i - 1);
    switch(ch) {
      case 'A':
        ret += 'T';
      break;
      case 'C':
        ret += 'G';
      break;
      case 'G':
        ret += 'C';
      break;
      case 'T':
        ret += 'A';
      break;
      case '(':
        ret += ')';
      break;
      case ')':
        ret += '(';
      break;
      case '[':
        ret += ']';
      break;
      case ']':
        ret += '[';
      break;
      case 'N':
        ret += 'N';
      break;
    }
  }

  return ret;
}

int main(int argc, char **argv)
{
  int ch;
  static struct option longopts[] = {
    { "input-file" , required_argument, NULL, 'i' },
    { "output-file", required_argument, NULL, 'o' },
    { "pattern"    , required_argument, NULL, 'p' },
    { "mismatch"   , required_argument, NULL, 'm' },
    { "pattern-min", required_argument, NULL, 'n' },
    { "label"      , required_argument, NULL, 'l' },
    { NULL         , 0                , NULL, 0   }
  };

  std::string commandLine;
  for (auto i = 0; i < argc; ++i)
    commandLine += argv[i] + std::string(" ");

  char *appName = argv[0];
  std::string inputFile, outputFile;

  std::vector<std::string> patterns;
  std::vector<std::string> labels;
  std::vector<uint16_t>    minNumberOfPatterns;
  uint16_t mismatchesAllowed = 0;

  while ((ch = getopt_long(argc, argv, "i:o:p:m:n:l:", longopts, NULL)) != -1) {
    switch (ch) {
      case 'i':
        if (!inputFile.empty())
          printUsage(appName);

        inputFile = optarg;
      break;
      case 'o':
        if (!outputFile.empty())
          printUsage(appName);

        outputFile = optarg;
      break;
      case 'p':
        patterns.push_back(optarg);
      break;
      case 'm':
        mismatchesAllowed = atoi(optarg);
      break;
      case 'n':
        minNumberOfPatterns.push_back(atoi(optarg));
      break;
      case 'l':
        labels.push_back(optarg);
      break;
      default:
        printUsage(appName);
     }
  }

  if (patterns.empty() || inputFile.empty() || outputFile.empty())
    printUsage(appName);

  if (patterns.size() != minNumberOfPatterns.size() || patterns.size() != labels.size())
    printUsage(appName);

  HunT hunt(mismatchesAllowed);

  for (size_t i = 0; i < patterns.size(); ++i) {
    try {
      hunt.addStateMachine(StateMachine(labels.at(i), patterns.at(i), minNumberOfPatterns.at(i), '+'));
      hunt.addStateMachine(StateMachine(labels.at(i), createComplement(patterns.at(i)), minNumberOfPatterns.at(i), '-'));
    }
    catch (ParseException &e) {
      std::cerr << "ERROR: " << e.what() << std::endl;
      return 1;
    }
  }

  Summary summary(outputFile);
  Output  output(outputFile);

  output.createHeader();
  summary.createHeader(commandLine);

  int ret = 0;
  size_t counter = 0;
  try {
    hunt.execute(inputFile, [&] (const std::string &geneName, const std::string &geneSequence,
      const std::vector<PositionToMark> &positions, const std::vector<HIT> &hit) {
      std::string name = geneName;
      if (!name.empty())
        name.erase(0, 1);
      summary.appendGene(name, hit);
      output.appendGene(name, geneSequence, positions);
      ++counter;
    });
  }
  catch (HunTException &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    ret = 1;
  }

  summary.createFooter(counter);
  output.createFooter();

  return ret;
}
