
#include "timetable.h"

std::ostream& timetable::print( std::ostream& out ) const
{
   out << "Performance table of " << algname;
   out << " (inputsize/runtime in seconds):\n";
   out << std::scientific;
   for( auto t : times )
   {
      out << "     " << t. first << "/";
      out << std::setprecision(4) << t. second;
   }
   out << "\n";

   return out;
}

