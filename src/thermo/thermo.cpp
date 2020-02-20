/*---------------------------------------------------------------------------*\
  c-o-o-c-o-o-o             |
  |     |     A utomatic    | Open Source Flamelet
  c-o-o-c     F lamelet     | 
  |     |     C onstructor  | Copyright (C) 2015 Holzmann-cfd
  c     c-o-o-o             |
-------------------------------------------------------------------------------
License
    This file is part of Automatic Flamelet Constructor.

    AFC is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 3 of the License, or 
    (at your option) any later version.

    AFC is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with AFC; if not, see <http://www.gnu.org/licenses/>

\*---------------------------------------------------------------------------*/

#include "thermo.hpp"
#include "constants.hpp"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

AFC::Thermo::Thermo
(
    const string fileName,
    const bool thermo
)
:
    thermoData_(thermo)
{
    ThermoReader thermoReader(fileName);

    thermoReader.read(thermoData_);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

AFC::Thermo::~Thermo()
{}


// * * * * * * * * * * * * * * * Insert Functions  * * * * * * * * * * * * * //

void AFC::Thermo::p
(
    const scalar pressure
)
{
    thermoData_.p(pressure);
}


// * * * * * * * * * * * * * * * Return Functions  * * * * * * * * * * * * * //

AFC::scalar AFC::Thermo::p() const
{
    return thermoData_.p();
}


AFC::wordList AFC::Thermo::species() const
{
    return thermoData_.species();
}


AFC::map<AFC::word, AFC::scalar> AFC::Thermo::MW() const
{
    return thermoData_.MW();
}


AFC::scalar AFC::Thermo::MW(const word species) const
{
    return thermoData_.MW(species);
}


AFC::scalar AFC::Thermo::MWmeanX(const map<word, scalar>& X) const
{
    return thermoCalc_.MWmeanX(X, MW());    
}


AFC::scalar AFC::Thermo::cp(const word species, const scalar T) const
{
    return thermoCalc_.cp(species, T, thermoData_);
}


AFC::scalar AFC::Thermo::cv(const word species, const scalar T) const
{
    return thermoCalc_.cv(species, T, thermoData_);
}


AFC::scalar AFC::Thermo::H(const word species, const scalar T) const
{
    return thermoCalc_.H(species, T, thermoData_);
}


AFC::scalar AFC::Thermo::S(const word species, const scalar T) const
{
    return thermoCalc_.S(species, T, thermoData_);
}


AFC::scalar AFC::Thermo::G(const word species, const scalar T) const
{
    return thermoCalc_.G(species, T, thermoData_);
}


AFC::scalar AFC::Thermo::G(const scalar H, const scalar S, const scalar T) const
{
    return thermoCalc_.G(H, S, T);
}


AFC::scalar AFC::Thermo::Hf(const word species) const
{
    return thermoCalc_.Hf(species, thermoData_);
}


AFC::scalar AFC::Thermo::Gf(const word species) const
{
    return thermoCalc_.Gf(species, thermoData_);
}


AFC::scalar AFC::Thermo::dHf(const word species, const scalar T) const
{
    return thermoCalc_.dHf(species, T, thermoData_);
}


AFC::scalar AFC::Thermo::dGf(const word species, const scalar T) const
{
    return thermoCalc_.dGf(species, T, thermoData_);
}


AFC::scalar AFC::Thermo::C(const scalar T) const
{
    return thermoCalc_.C(p(), T);
}


AFC::scalar AFC::Thermo::rho(const word species, const scalar T) const
{
    return thermoCalc_.rho(T, p(), MW(species));
}


AFC::word AFC::Thermo::phase(const word species) const
{
    return thermoData_.phase(species);
}

// * * * * * * * * * * * * * * Summary Function  * * * * * * * * * * * * * * //


void AFC::Thermo::summary(ostream& data) const
{
    //- Header
    data<< Header() << "\n"; 

    const wordList& species = thermoData_.species();
    const wordList& formula = thermoData_.formula();

    data<< " c-o Thermodynamic summary:\n"
        << " ==========================\n\n"
        << " Species in thermo: " << species.size() << "\n";

    data<< " \n\n Species used:\n";
    data<< std::left;

    forEach(species, s)
    {
        data<< "    |--> "
            << std::setw(20) <<  species[s]
            << "(" << formula[s] << ")\n";
    }

    //- Build table with all NASA coeffs for all species
    NASAPolynomials(data, "LOW");
    NASAPolynomials(data, "HIGH");

    //- Build thermoanalyse table
    thermoTable(data);

}


void AFC::Thermo::NASAPolynomials(ostream& data, const word coeff) const
{
    word range;

    if (coeff == "LOW")
    {
        range = "LOW";
    }
    else if (coeff == "HIGH")
    {
        range = "HIGH";
    }

    //- Header
    data<< "\n\n"
        << "=================================================================="
        << "=================================================================="
        << "================\n"
        << " c-o NASA POLYNOMIALS (" << range << " TEMPERATURE)\n"
        << "=================================================================="
        << "=================================================================="
        << "================\n\n"
        << " Species                |"
        << "         c1               c2               c3      "
        << "         c4               c5               c6      "
        << "         c7        |\n"
        << "------------------------------------------------------------------"
        << "------------------------------------------------------------------"
        << "----------------\n";

    //- Species of Thermodynamic Data
    const wordList& species = thermoData_.species();

    //- Build Table
    forEach(species, s)
    {

        List<scalar> NASA(7, 0);
        
        if (coeff == "LOW")
        {
            NASA = thermoData_.NASACoeffsLT(species[s]);
        }
        else if (coeff == "HIGH")
        {
            NASA = thermoData_.NASACoeffsHT(species[s]);
        }

        //- For species number + name
        std::ostringstream oss;

        oss << " (" << toStr(s+1) << ") " << species[s];
        
        data<< std::left << std::setw(22) << oss.str()
            << "  |" << std::right
            << std::setw(17) << NASA[0]
            << std::setw(17) << NASA[1]
            << std::setw(17) << NASA[2]
            << std::setw(17) << NASA[3]
            << std::setw(17) << NASA[4]
            << std::setw(17) << NASA[5] 
            << std::setw(17) << NASA[6]
            << "  |\n";
    }

    data<< "=================================================================="
        << "=================================================================="
        << "================\n\n";
}


void AFC::Thermo::thermoTable(ostream& data) const
{
    //- Species of Thermodynamic Data
    const wordList& species = thermoData_.species();
    const wordList& formula = thermoData_.formula();

    //_ Build the thermoanalyse table
    forEach(species, s)
    {
        const word& phase = thermoData_.phase(species[s]);

        data<< "==========================================================="
            << "=========================================================\n"
            << " c-o Thermo analyses for " << species[s] << "\n"
            << "==========================================================="
            << "=========================================================\n"
            << " Phase: " << phase << "\n"
            << " Formula: " << formula[s] << "\n"
            << " Composition: \n   |\n";

        const map<word, scalar>& elements =
            thermoData_.elementFactorsMap(species[s]);

        forAll(elements, a)
        {
            data<< "   |--> " << std::setw(4) << a.first
                << " " << a.second << "\n";
        }

        data<< "\n" << std::setw(40) << std::left
            <<" Molecular weight:   "
            << std::setw(14) << std::right
            << MW(species[s]) << " [g/mol]\n"
            << std::setw(40) << std::left
            << " Formation enthalpy (298K):   "
            << std::setw(14) << std::right
            << Hf(species[s]) << " [J/mol]\n"
            << std::setw(40) << std::left
            <<" Frormation free Gibbs energy (298K):   "
            << std::setw(14) << std::right
            << Gf(species[s]) << " [J/mol]\n";


        data<< std::right << "\n";

        data<< "\n\n-----------------------------------------------------------"
            << "---------------------------------------------------------\n"
            << "      T    |         cp              H               S       "
            << "        G              dHf            dGf          | \n"
            << "     [K]   |      [J/molK]        [J/mol]         [J/molK]   "
            << "     [J/mol]         [J/molK]       [J/mol]        | \n"
            << "-----------------------------------------------------------"
            << "---------------------------------------------------------\n";

        for(int i=300; i<=3000; i+=100)
        {
            data<< "  " << std::setw(6) << i << "   |" 
                << "  " << std::setw(13) << cp(species[s], i) 
                << "  " << std::setw(14) << H(species[s], i) 
                << "  " << std::setw(14) << S(species[s], i)
                << "  " << std::setw(14) << G(species[s], i)
                << "  " << std::setw(14) << dHf(species[s], i) 
                << "  " << std::setw(14) << dGf(species[s], i) 
                << "     |\n";
        }

        data<< " ----------------------------------------------------------"
            << "---------------------------------------------------------\n\n"
            << "\n\n";
    }
}


// ************************************************************************* //
