#include "Job.h"
#include <fstream>
#include <sstream>

#include "RisoInit.h"
#include "Helper.h" 

void
Job::dump(std::string filename) {
	std::ofstream outfile (filename.c_str());

	outfile << "\x1e\x52";

	std::stringstream s;

	outVarLen(outfile, risoInit, sizeof(risoInit), 'e');
	outFixedLen(outfile, "40;297;420", 'z');
	outFixedLen(outfile, "300;600", 'r');
	s << 250; outFixedLen(outfile, s.str(), 'C'); // copies
	outFixedLen(outfile, "1", 'J');
	outFixedLen(outfile, "1", 'G');
	outFixedLen(outfile, "5", 'S'); // optional
	outFixedLen(outfile, "1", 'D'); // optional

	// FIXME: HOST, FILE, TIME
	outVarLen(outfile, "\x1f""HOST0008\x1f""win_user", 'n');
	outVarLen(outfile, "\x1f""FILE0006\x1f""a3.pdf", 'n');
	outVarLen(outfile, "\x1f""TIME0016\x1f""15.06.2009 21:53", 'n');

	outFixedLen(outfile, "32;0;0;0", 'O');
	outFixedLen(outfile, "42;0;0;0", 'O');
	outFixedLen(outfile, "3;0;0;0", 's');
	outFixedLen(outfile, "104;0;0;0", 's');
	outFixedLen(outfile, "201;321;0;0", 's');
	outFixedLen(outfile, "211;106;2;0", 's');
	outFixedLen(outfile, "301;50;15;20", 's');
	//outFixedLen(outfile, "30;0;0;0", 'Q');

	for(unsigned int i = 0; i < m_Pages.size(); i++) {
	// Per Page: O; o; M;
		outFixedLen(outfile, "1033;0;0;0", 'O');
		//outFixedLen(outfile, "1001;34;1;3", 'o');
		outFixedLen(outfile, "1", 'M');

		// Page data
		m_Pages[i]->dumpRiso(outfile);

		outfile << "\x0c";
	}

	outfile << "\x1e\x52";

}

