#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <iostream>

/// Egy manualisabb idomero, ami a rendszeridot hasznalja.
/// A manualis resze abbol adodik, hogy amikor kell konkret ido adat,
/// akkor le kell (vagy akkor le lesz) frissitve, igy nem kell kulon
/// szalon futnia.
class Timer {
    time_t t0;  ///< Az idozito indulasanak pillanata
    time_t t;   ///< Az "aktualis" ido
public:
    /// Default Konstruktor
    Timer() : t0(time(nullptr)), t(t0) {};

    /// Jatek ujratoltese eseten elcsuszott ido ujra allitasa
    void CalibrateTime();

    /// frissiti a t-ben tarolt "aktualis", valamint visszaadja az eltelt idot
    /// @return A timer inicializalasa ota eltelt ido (time_t)
    time_t GetDeltaTime();
    /// @brief A kezdo ido elerese
    /// @return t0 erteke
    time_t GetT0() const {return t0;}
    /// @brief Az aktualis ido elerese
    /// @return t erteke
    time_t GetT() const {return t;}
    /// Kiiros fuggveny ostream-mekre
    friend std::ostream& operator<<(std::ostream& os, const Timer& timer);
    /// Beolvaso fuggveny istream-mekrol
    friend std::istream& operator>>(std::istream& is, Timer& timer);
};

std::ostream& operator<<(std::ostream& os, const Timer& timer);
std::istream& operator>>(std::istream& is, Timer& timer);

#endif //TIMER_H
