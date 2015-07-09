/*---------------------------------------------------------------------------*\
| =========                |                                                  |
| \\      /  A utomatic    | Holzmann-cfd                                     |
|  \\    /   F lamelet     | Version: 1.0                                     |
|   \\  /    C onstructor  | Web: www.Holzmann-cfd.de                         |
|    \\/                   |                                                  |
\*---------------------------------------------------------------------------*/
/*
�
�
�
�
�
�
�
�
�
�
\*---------------------------------------------------------------------------*/
#ifndef Thermodynamic_hpp
#define Thermodynamic_hpp
//- system headers
#include <math.h>
//- user def. headers
#include "../definitions/typedef.hpp"
#include "../transport/transport.hpp"


class Thermodynamic
:
    public Transport
{
    public:

        //- constructor
        Thermodynamic();

        //- destructor
        ~Thermodynamic();


    public:

    //- functions
    //-----------

        //- read thermo file
        void readThermodynamicFile
        (
            const normalString&,
            const stringField&
        );

        //- read the NASA polynoms
        void readNASA
        (
            const stringField&,
            const unsigned int&,
            const stringField&
        );

        //- increment all matrixes and vectors
        void thermodynamicDataIncrement();

        //- calculate molecular weight of species
        void calcMolecularWeight
        (
            const normalString&
        );

        // return value of NASA_ vector
        bool NASA
        (
            const unsigned int&
        ) const;

        //- return moleculare weight
        scalar MW(const unsigned int&) const;

        //- set phase
        void setPhase( const normalString& );

        //- set temperature bounds
        void setPolyTemperature( const scalar&, const scalar&, const scalar& );

        //- set polyCoeffs
        void setPolyCoeffs( const scalarField& );

        //- return heat capacity cp [J/(molK)]
        scalar cp( const scalar ) const;

        //- return enthalpy [J/(mol)]
        scalar h( const scalar ) const;

        //- return ref enthalpy [J/mol]
        scalar h0() const;

        //- calculate entropie S [J/(molK)]
        scalar s( const scalar ) const;

        //- calculate free gibbs energy
        scalar G( const scalar ) const;

        //- set thermodynamic status
        void thermodynamicTrue();

        //- return thermodynamic status
        bool thermodynamicStatus() const;

        //- define the
        void whichPolyCoeffs( const scalar&, int& ) const;




    private:

    //- variables
    //-----------

        //- phase
        normalString phase;

        //- themodynamic values set
        bool thermoBool;

        //- temperature bounds
        scalar lowTemp;
        scalar comTemp;
        scalar higTemp;

        //- NASA coeffs for each species that is involved in the meachanism
        matrix NASACoeffs_;

        //- bool switch (if NASA found set to true) otherwise its false
        //  necessary for checking if for all species polynomials found
        std::vector<bool> NASA_;

        //- moleculare weight of species
        scalarField MW_;

        //- special variables

            //- this variable is changed during setting up the NASA coeffs
            //  it contains the ID of the species that is read at the moment
            unsigned int speciesId_;
//
//        //- mid temperature
//        int T_mid{0};
//
//        //- high temperature
//        int T_high{0};
//
//        //- high temperature coefficients (NASA-P)
//        double a1{0.}, a2{0.}, a3{0.}, a4{0.}, a5{0.}, a6{0.}, a7{0.};
//
//        //- low temperature coefficient (NASA-P)
//        double b1{0.}, b2{0.}, b3{0.}, b4{0.}, b5{0.}, b6{0.}, b7{0.};
};


#endif // Thermodynamic_hpp
