/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#include "h/globals.h"

void monitor_chan (const char *message, int channel);

const string Utils::_FormatString( const sint_t narg, const bitset<MAX_BITSET> flags, const string caller, const string fmt, ... )
{
    va_list args;
    string output;

    va_start( args, fmt );
    output = __FormatString( narg, flags, caller, fmt, args );
    va_end( args );

    return output;
}

const string Utils::__FormatString( const sint_t narg, const bitset<MAX_BITSET> flags, const string caller, const string fmt, va_list val ) // Thanks go to Darien @ MudBytes.net for the start of this
{
    va_list args;
    vector<string> arguments;
    vector<string>::iterator si;
    vector<char> buf;
    string output, token;
    sint_t size = 0;

    arguments = StrTokens( fmt );
    for ( si = arguments.begin(); si != arguments.end(); si++ )
    {
        token = *si;
        if ( token.find( "%" ) != string::npos ) // not foolproof, but it should catch some worst cases by attempting
            size++;                              // to ensure a matching narg : format specifier count
    }

    if ( narg != 1 && narg != size )
    {
        Logger( flags, "ERROR: Number of arguments (%ld) did not match number of format specifiers (%ld) at: %s", narg, size, caller.c_str() );
        return output = "";
    }

    va_copy( args, val );
    size = vsnprintf( NULL, 0, fmt.c_str(), args );
    va_end( args );

    va_copy( args, val );
    buf.resize( size + 1 );
    vsnprintf( &buf[0], ( size + 1 ), fmt.c_str(), args );
    va_end( args );

    return output = &buf[0];
}

const void Utils::_Logger( const sint_t narg, const bitset<MAX_BITSET> flags, const string caller, const string fmt, ... )
{
    va_list args;
    string output;

    va_start( args, fmt );
    output = __FormatString( narg, flags, caller, fmt, args );
    va_end( args );

    if ( output.empty() )
        return;

    if ( flags.test(UTILS_DEBUG) ) // output caller
        clog << current_time_str() << " :: " << output << " [" << caller << "]" << endl;
    else
        clog << current_time_str() << " :: " << output << endl;
    if ( !server.shutdown )
        monitor_chan( output.c_str(), MONITOR_LOG );

    return;
}

const bool Utils::PatternMatch( const bitset<MAX_BITSET> flags, const string pat, const string str )
{
    uint_t pi = 0, si = 0,  px = 0, sx = 0;
    char ppat = '\0';
    //char pstr = '\0';
    bool found = true;

    // assign pi to pattern length, si to str length
    // use px as temporary incrementing pi, use sx as temporary incrementing si

    // special cases for quick processing
    if ( pat[0] == '.' && pat[1] == '*' && pat[2] == '\0' ) // .* -- match anything until end
    {
        if ( flags.test( UTILS_DEBUG ) )
            Logger( 0, "pat: %s -- str: %s -- found: %d", pat.c_str(), str.c_str(), found );
        return found = true;
    }

    if ( pat[0] == '*' && pat[1] == '\0' ) // * -- nothing preceding to match
    {
        if ( flags.test( UTILS_DEBUG ) )
            Logger( 0, "pat: %s -- str: %s -- found: %d", pat.c_str(), str.c_str(), found );
        return found = false;
    }

    while ( pat[pi] != '\0' && str[si] != '\0' && found )
    {
        px = pi;
        sx = si;

        if ( flags.test( UTILS_DEBUG ) )
            Logger( 0, "pi: %lu -- si: %lu -- pat[pi] %c -- str[si] %c", pi, si, pat[pi], str[si] );

        switch( pat[pi] )
        {
            case '.':
                if ( pat[++px] != '\0' && str[++sx] == '\0' && found ) // pattern is longer than our string, and not ending in a wildcard match
                {
                    found = false;

                    if ( flags.test( UTILS_DEBUG ) )
                        Logger( 0, "notfound -- pat[++px]: %c -- str[sx]: %c", pat[px], str[sx] );
                    break;
                }

                found = true;
            break;

            case '*':
                if ( ppat == '\0' )      {       found = false; break; }
                if ( ppat == str[++sx] ) { pi--; found = true;  break; }
            break;

            case '\\': found = ( pat[++pi] == str[si] ); break;

            default:
                if ( pat[++px] != '\0' && str[++sx] == '\0' && found ) // pattern is longer than our string, and not ending in a wildcard match
                {
                    found = false;

                    if ( flags.test( UTILS_DEBUG ) )
                        Logger( 0, "notfound -- pat[++px]: %c -- str[sx]: %c", pat[px], str[sx] );
                    break;
                }

                found = ( pat[si] == str[si] );
                if ( flags.test( UTILS_DEBUG ) )
                    Logger( 0, "default -- pat[pi]: %c -- str[si]: %c -- found: %d", pat[pi], str[si], found );
            break;
        }

        ppat = pat[pi];
        //pstr = str[si];
        pi++;
        si++;
    }

    if ( flags.test( UTILS_DEBUG ) )
        Logger( 0, "patternmatch -- pat: %s -- str %s -- found: %d", pat.c_str(), str.c_str(), found );

    return found;
}

const vector<string> Utils::StrTokens( const string input )
{
    stringstream ss( input );
    istream_iterator<string> si( ss );
    istream_iterator<string> end;
    vector<string> output( si, end );

    return output;
}
