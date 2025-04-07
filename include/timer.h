#ifndef TIMER_H
#define TIMER_H

#include <ctime>

/// Egy manualisabb idozito, ami a rendszeridot hasznalja.
/// A manualis resze abbol adodik, hogy amikor kell konkret ido adat,
/// akkor le kell (vagy akkor le lesz) frissitve, igy nem kell kulon
/// szalon futnia.
class Timer {
    time_t t0;
    time_t t;
public:
    Timer() : t0(time(nullptr)), t(t0) {};

    /// Jatek ujratoltese eseten elcsuszott ido ujra allitasa
    void CalibrateTime();

    /// frissiti a t-ben tarolt "aktualis", valamint visszaadja az eltelt idot
    /// @return A timer inicializalasa ota eltelt ido (time_t)
    time_t GetDeltaTime();

};

#endif //TIMER_H
