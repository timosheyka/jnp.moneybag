#include <iostream>
#include <string>
#include <cassert>
#include <stdbool.h>

class Moneybag {
public:
    typedef uint64_t coin_number_t;
    
private:
	coin_number_t livre;	
    coin_number_t solidus;
    coin_number_t denier;	
public: 
    // KONSTRUKTORY I GETTERY
	constexpr Moneybag(coin_number_t l, coin_number_t s, coin_number_t d) 
	    : livre(l), solidus(s), denier(d){}
	    
	constexpr Moneybag(const Moneybag &m) 
	    : livre(m.livre), solidus(m.solidus), denier(m.denier){}

    constexpr int livre_number() const { return livre; }
    constexpr int solidus_number() const { return solidus; }
    constexpr int denier_number() const { return denier; }
    
    // OPERATORY
	explicit operator bool() const {
		if (livre == 0 && denier == 0 && solidus == 0) {
			return false;
		}
		else {
			return true;
		}
    } 
	void operator =(const Moneybag &m) {
		livre = m.livre;
		solidus = m.solidus;
		denier = m.denier;
	}
	Moneybag operator +(const Moneybag &m) const {
		// TODO: overflowy
		return Moneybag(livre + m.livre, solidus + m.solidus, denier + m.denier);
	}
		
	Moneybag& operator+=(const Moneybag &m){
		// TODO: overflowy
		livre += m.livre;
		solidus += m.solidus;
		denier += m.denier;
        return *this;
    }
	
	Moneybag operator -(const Moneybag &m) const {
		// TODO: sprawdzanie czy nie wychodzi ujemne
		return Moneybag(livre - m.livre, solidus - m.solidus, denier - m.denier);
	}
	
	Moneybag operator *(const uint64_t c) const {
		// TODO: overflowy
		return Moneybag(livre * c, solidus * c, denier * c);
	}
	
	bool operator ==(const Moneybag &m) {
		if (livre == m.livre && denier == m.denier && solidus == m.solidus) {
			return true;
		}
		else {
			return false;
		}
	}
	std::partial_ordering operator<=>(Moneybag const &m) const {
        if (livre > m.livre && denier >= m.denier && solidus >= m.solidus) {
          return std::partial_ordering::greater;
	    }
	    else if (livre >= m.livre && denier > m.denier && solidus >= m.solidus) {
          return std::partial_ordering::greater;
	    }
        else if (livre >= m.livre && denier >= m.denier && solidus > m.solidus) {
          return std::partial_ordering::greater;
	    }
        else if (livre == m.livre && denier == m.denier && solidus == m.solidus) {
          return std::strong_ordering::equal;
	    }	
        if (livre < m.livre && denier <= m.denier && solidus <= m.solidus) {
          return std::partial_ordering::less;
	    }
	    else if (livre <= m.livre && denier < m.denier && solidus <= m.solidus) {
          return std::partial_ordering::less;
	    }
        else if (livre <= m.livre && denier <= m.denier && solidus < m.solidus) {
          return std::partial_ordering::less;
	    }
	    else {
			return std::partial_ordering::unordered;
		}
    }
    
    // TO_STRING
    std::string toString() const {
		// TODO: naprawić dla jednej monety
		std::string res = "(" + std::to_string(livre) + " livres, "
		+ std::to_string(solidus) + " soliduses, "
		+ std::to_string(denier) + " deniers)";
		return res;
	}
};

std::ostream &operator<<(std::ostream &os, Moneybag const &m) { 
    return os << m.toString();
}

const Moneybag Livre = Moneybag(1, 0, 0);
const Moneybag Solidus = Moneybag(0, 1, 0);
const Moneybag Denier = Moneybag(0, 0, 1);

// żeby działało Moneybag * int (idk czy jest jakiś lepszy sposób)
Moneybag operator *(const uint64_t c, const Moneybag &m) {
	return Moneybag(m.livre_number() * c,  m.solidus_number() * c, m.denier_number() * c);
}
