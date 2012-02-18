/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#define DEC_BRAIN_H

class Brain {
    public:
        Brain();
        ~Brain();

        string GetHost() const { return m_host; }
        char* GetHost_() const { return const_cast<char*>( GetHost().c_str() ); }
        string SetHost( const string host ) { return m_host = host; }

    private:
        string m_host;
};
