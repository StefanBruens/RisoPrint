#include <Job.h>
#include <ImageFile.h>
#include <cstring>

int main(int argc, char* argv[])
{
	Job job;
	ImageFile im;
	int ret = -1;
	std::string outfile("/tmp/out.prn");

	if( (argc > 1) && (0 == memcmp("-o", argv[1], 2))) {
		outfile = std::string(argv[2]);
		if( argc == 4 )
			ret = im.openFile( std::string(argv[3]) );
	} else {
		if( argc == 2 )
			ret = im.openFile( std::string(argv[1]) );
	}

	if(ret < 0)
		return ret;

	PageSptr page;
	while(im.read(page)) {
		job.addPage(page);
		//page->dumpImage();
		page->encode();
		// page->dumpImage("/tmp/N");
	}

	job.dump(outfile);

	return ret;
}
