#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>
 
#include <fastcgi++/request.hpp>
#include <fastcgi++/manager.hpp>
 
void error_log(const char* msg)
{
        using namespace std;
        using namespace boost;
        static ofstream error;
        if(!error.is_open())
        {
                error.open("/tmp/errlog", ios_base::out | ios_base::app);
                error.imbue(locale(error.getloc(), new posix_time::time_facet()));
        }
 
        error << '[' << posix_time::second_clock::local_time() << "] " << msg << endl;
}
 
class Helloworld : public Fastcgipp::Request<char>
{
public:
        bool response()
        {
				out << "Content-Type: text/html;\r\n\r\n";
                out << "<html><body>";
                out << "Hello worldXXXXX!<br />";
                out << "</body></html>";
                return true;
        }  
};
int main(int argc,char** argv)
{
        try
        {
                Fastcgipp::Manager<Helloworld> fcgi;
                fcgi.handler();
        }
        catch(std::exception& e)
        {
                error_log(e.what());
        }
}
