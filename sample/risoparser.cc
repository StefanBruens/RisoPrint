#include <JobFile.h>

int main(int argc, char* argv[])
{
	JobFile job;
	int ret;

	if( argc == 2 )
		ret = job.openFile( std::string(argv[1]) );

	if(ret < 0)
		return ret;

	ret = job.parse();

	return ret;
}
