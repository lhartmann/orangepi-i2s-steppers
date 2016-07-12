#ifndef TRANSPORTDELAY_H
#define TRANSPORTDELAY_H

/// Generic transport delay buffer
/** @param T   type of data in the buffer.
 *  @param N   number os samples todelay.
 */
template <class T, int N> class TransportDelay {
    T buff[N]; //!< Delay buffer
    T *p;      //!< Current sample pointer

public:
    TransportDelay() : p(buff+N) {}
    T operator() (T x) {
        // Advance pointer
        if (p == buff) p += N-1;
        else p--;

        // Exchange data
        T y = *p;
        *p = x;

        return y;
    }
};

#endif // TRANSPORTDELAY_H

