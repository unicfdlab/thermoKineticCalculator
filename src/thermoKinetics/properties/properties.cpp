/*---------------------------------------------------------------------------*\
  c-o-o-c-o-o-o             |
  |     |     A utomatic    | Open Source Flamelet
  c-o-o-c     F lamelet     |
  |     |     C onstructor  | Copyright (C) 2020 Holzmann CFD
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

#include "properties.hpp"
#include "constants.hpp"
#include <cmath>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

AFC::Properties::Properties
(
    const string fileName,
    const Thermo& thermo,
    const Chemistry& chemistry
)
:
    PropertiesCalc(fileName, thermo, chemistry)
{
    //- Add pressure to thermoData for better handling
    //thermo.p(this->p());

    //- Convert Y to X or X to Y
    /*convertFractions();

    //- Extract the single atomic elements
    {
        oxidizerA_ =
            PropertiesCalc::elementDecomposition(speciesOxidizer_, thermo_);


        fuelA_ = PropertiesCalc::elementDecomposition(speciesFuel_, thermo_);
    }

    //- Calc the element mass fraction
    {
        oxidizerZj_ =
            PropertiesCalc::elementMassFraction
            (
                oxidizerA_,
                oxidizerY_,
                thermo_
            );

        fuelZj_ =
            PropertiesCalc::elementMassFraction
            (
                fuelA_,
                fuelY_,
                thermo_
            );


        //- Assign the element mass fractions of the fuel and oxidizer species
        //  Used for the stochiometric calculation

    }

    //- Calc the element mole fraction
    {
        oxidizerWj_ =
            PropertiesCalc::elementMolFraction(oxidizerZj_, thermo_);

        fuelWj_ =
            PropertiesCalc::elementMolFraction(fuelZj_, thermo_);
    }

    //- Calc the stochiometric fraction Zst
    scalar oxidizer, fuel;

        oxidizer = oxidizerY_.at(oxidizer_);
        fuel = fuelY_.at(fuel_);

        Info<< oxidizer << ":" << fuel << endl;

    Zst_ = PropertiesCalc::Zst
        (
            fuelZj_,
            fuelY_.at(fuel_),
            oxidizerY_.at(oxidizer_),
            thermo_
         );

    Info << "Zst = " << Zst_ << endl;


    std::terminate();

    //- Initialize 
    //scalar a = PropertiesCalc::Zst(fuelY(), oxidizerY());
    */
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

AFC::Properties::~Properties()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

/*
void AFC::Properties::fuelSpecies(const word fuel)
{
    fuel_ = fuel;
}


void AFC::Properties::oxidizerSpecies(const word oxidizer)
{
    oxidizer_ = oxidizer;
}


void AFC::Properties::inertSpecies(const word inert)
{
    inert_ = inert;
}


void AFC::Properties::insertMFPoints(const int nZPoints)
{
    nZPoints_ = nZPoints;
}


void AFC::Properties::insertVMFPoints(const int nZvarPoints)
{
    nZvarPoints_ = nZvarPoints;
}


void AFC::Properties::insertEnthalpyDefects(const scalar defect)
{
    defects_.push_back(defect);
}


void AFC::Properties::insertScalarDissipationRates(const scalar sDR)
{
    sDRs_.push_back(sDR);
}


void AFC::Properties::insertTemperatureOxidizer(const scalar TOxidizer)
{
    TOxidizer_ = TOxidizer;
}


void AFC::Properties::insertTemperatureFuel(const scalar TFuel)
{
    TFuel_ = TFuel;
}


void AFC::Properties::insertCompositionOxidizerMol
(
    const word species,
    const scalar molFraction
)
{
    speciesOxidizer_.push_back(species);

    oxidizerX_[species] = molFraction;
    oxidizerY_[species] = 0;
}


void AFC::Properties::insertCompositionOxidizerMass
(
    const word species,
    const scalar massFraction
)
{
    speciesOxidizer_.push_back(species);

    oxidizerY_[species] = massFraction;
    oxidizerX_[species] = 0;
}


void AFC::Properties::insertCompositionFuelMol
(
    const word species,
    const scalar molFraction
)
{
    speciesFuel_.push_back(species);

    fuelX_[species] = molFraction;
    fuelY_[species] = 0;
}


void AFC::Properties::insertCompositionFuelMass
(
    const word species,
    const scalar massFraction
)
{
    speciesFuel_.push_back(species);

    fuelY_[species] = massFraction;
    fuelX_[species] = 0;
}


void AFC::Properties::insertRunTime(const scalar runTime)
{
    runTime_ = runTime;
}


void AFC::Properties::insertWriteControl(const word writeControl)
{
    writeControl_ = writeControl;
}


void AFC::Properties::insertWriteControlInterval
(
    const scalar writeControlInterval
)
{
    writeControlInterval_ = writeControlInterval;
}


void AFC::Properties::insertWriteControlTime(const scalar writeControlTime)
{
    writeControlTime_ = writeControlTime;
}


void AFC::Properties::insertDeltat(const scalar deltat)
{
    deltat_ = deltat;
}


void AFC::Properties::insertPressure(const scalar pressure)
{
    p_ = pressure;
}


void AFC::Properties::inputMol()
{
    inputMol_ = true;
}


void AFC::Properties::inputMass()
{
    inputMass_ = true;
}


void AFC::Properties::insertInterpreter
(
    const word keyword
)
{
    interpreter_ = keyword;
}


// * * * * * * * * * * * * * Time Related Functions  * * * * * * * * * * * * //

void AFC::Properties::updateCurrentTime(const scalar time)
{
    currentTime_ = time;
}


AFC::scalar AFC::Properties::runTime() const
{
    return runTime_;
}


AFC::scalar AFC::Properties::deltat() const
{
    return deltat_;
}


AFC::scalar AFC::Properties::currentTime() const
{
    return currentTime_;
}


AFC::scalar AFC::Properties::write() const
{
    return writeControlTime_;
}


// * * * * * * * * * * * * * * * Other functions * * * * * * * * * * * * * * //

void AFC::Properties::initialBoundary()
{
    const wordList& species = chemistry_.species();

    forAll(species, s)
    {
        oxidizerX_[s] = 0.;
        oxidizerY_[s] = 0.;

        fuelX_[s] = 0.;
        fuelY_[s] = 0.;
    }
}


void AFC::Properties::check()
{
    if (nZPoints_ == 0)
    {
        ErrorMsg
        (
            "No mixtureFractionPoints defined in the afcDict.",
            __FILE__,
            __LINE__
        );
    }

    if (nZvarPoints_ == 0)
    {
        ErrorMsg
        (
            "No varianzOfMixtureFractionPoints defined in the afcDict.",
            __FILE__,
            __LINE__
        );
    }

    if (TOxidizer_ == 0)
    {
        ErrorMsg
        (
            "No temperature for oxidizer defined in the afcDict.",
            __FILE__,
            __LINE__
        );
    }

    if (TFuel_ == 0)
    {
        ErrorMsg
        (
            "No temperature for fuel defined in the afcDict.",
            __FILE__,
            __LINE__
        );
    }

    if (sDRs_.empty())
    {
        ErrorMsg
        (
            "No scalar dissipation rates defined in the afcDict.",
            __FILE__,
            __LINE__
        );
    }

    if
    (
        oxidizerX_.empty()
     && oxidizerY_.empty()
    )
    {
        ErrorMsg
        (
            "No oxidizer species defined in the afcDict.",
            __FILE__,
            __LINE__
        );
    }

    if
    (
        fuelX_.empty()
     && fuelY_.empty()
    )
    {
        ErrorMsg
        (
            "No fuel species defined in the afcDict.",
            __FILE__,
            __LINE__
        );
    }

    scalar sum{0};

    scalar epsilon{1e-12};

    if (inputMol_)
    {
        //- Oxidizer
        forAll(speciesOxidizer_, s)
        {
            sum += oxidizerX_.at(s);
        }

        //- Double comparison; with epsilon
        if ((1.0 - sum) > epsilon)
        {
            ErrorMsg
            (
                "Sum of mol fraction of oxidizer is not 1 ("
                + std::to_string(sum) + ").\n    "
                "Please check your fraction composition for the oxidizer "
                "stream in your afcDict.",
                __FILE__,
                __LINE__
            );
        }

        //- Fuel
        sum = 0;

        forAll(speciesFuel_, s)
        {
            sum += fuelX_.at(s);
        }

        //- Double comparison; with epsilon
        if ((1.0 - sum) > epsilon)
        {
            ErrorMsg
            (
                "Sum of mol fraction of fuel is not 1 ("
                + std::to_string(sum) + ").\n    "
                "Please check your fraction composition for the fuel "
                "stream in your afcDict.",
                __FILE__,
                __LINE__
            );
        }
    }
    else if (inputMass_)
    {
        //- Oxidizer
        forAll(speciesOxidizer_, s)
        {
            sum += oxidizerY_.at(s);
        }

        //- Double comparison; with epsilon
        if ((1.0 - sum) > epsilon)
        {
            ErrorMsg
            (
                "Sum of mass fraction of oxidizer is not 1 ("
                + std::to_string(sum) + ").\n    "
                "Please check your fraction composition for the oxidizer "
                "stream in your afcDict.",
                __FILE__,
                __LINE__
            );
        }

        //-Fuel
        sum = 0;

        forAll(speciesFuel_, s)
        {
            sum += fuelY_.at(s);
        }

        //- Double comparison; with epsilon
        if ((1.0 - sum) > epsilon)
        {
            ErrorMsg
            (
                "Sum of mass fraction of fuel is not 1 ("
                + std::to_string(sum) + ").\n    "
                "Please check your fraction composition for the fuel "
                "stream in your afcDict.",
                __FILE__,
                __LINE__
            );
        }
    }
    else
    {
        ErrorMsg
        (
            "Either mol fraction or mass fraction defined for oxidizer"
            " stream.",
            __FILE__,
            __LINE__
        );
    }

    //- Check if pressure is set
    if (p_ <= 0)
    {
        ErrorMsg
        (
            "Pressure is not set or set not correct.\n    "
            "Please set the pressure in afcDict.",
            __FILE__,
            __LINE__
        );
    }

    //- Check if oxidizer is set and inside the oxidizer species list
    {
        if (oxidizer_.empty())
        {
            ErrorMsg
            (
                "    No oxidizer species is set.\n"
                "    Please check the oxidizer keyword in afcDict.",
                __FILE__,
                __LINE__
            );
        }

        if(oxidizerY_.find(oxidizer_) == oxidizerY_.end())
        {
            ErrorMsg
            (
                "    The oxidizer species '" + oxidizer_ + "' was not found"
                " in the oxidizer mass- or moleFraction dictionary.\n"
                "    Please check the afcDict.",
                __FILE__,
                __LINE__
            );
        }
    }
    
    //- Check if fuel is set and inside the fuel species list
    {
        if (fuel_.empty())
        {
            ErrorMsg
            (
                "    No fuel species is set.\n"
                "    Please check the fuel keyword in afcDict.",
                __FILE__,
                __LINE__
            );
        }

        if(fuelY_.find(fuel_) == fuelY_.end())
        {
            ErrorMsg
            (
                "    The fuel species '" + fuel_ + "' was not found"
                " in the fuel mass- or moleFraction dictionary.\n"
                "    Please check the afcDict.",
                __FILE__,
                __LINE__
            );
        }
    }
}


void AFC::Properties::convertFractions()
{
    //- Convert to mass fraction
    if (inputMol_)
    {
        XtoY(oxidizerX_, oxidizerY_);
        XtoY(fuelX_, fuelY_);
    }
    //- Convert to mol fraction
    else if (inputMass_)
    {
        YtoX(oxidizerY_, oxidizerX_);
        YtoX(fuelY_, fuelX_);
    }
    //- Already checked within the check() function. However,
    //  maybe something might go wrong - an additional check is okay here
    else
    {
        ErrorMsg
        (
            "Some problem occurs regarding input mode (mass, mole)",
            __FILE__,
            __LINE__
        );
    }
}

void AFC::Properties::XtoY(const map<word, scalar>& X, map<word, scalar>& Y )
{
    scalar M{0};

    //- Calculate M
    loopMap(species, value, X)
    {
       M += value * thermo_.MW(species); 
    }

    //- Calculate Y
    loopMap(species, value, X)
    {
        Y.at(species) = value*thermo_.MW(species) / M;
    }
}


void AFC::Properties::YtoX(const map<word, scalar>& Y, map<word, scalar>& X)
{
    scalar M{0};
    scalar YbyM{0};

    //- Calculate YbyM
    loopMap(species, value, Y)
    {
        YbyM += value / thermo_.MW(species);    
    }

    M = pow(YbyM, -1);

    loopMap(species, value, Y)
    {
        X.at(species) = M * value / thermo_.MW(species);
    }
}


// * * * * * * * * * * * * * * * Return Functions  * * * * * * * * * * * * * //

AFC::word AFC::Properties::fuel() const
{
    return fuel_;
}


AFC::word AFC::Properties::oxidizer() const
{
    return oxidizer_;
}


AFC::word AFC::Properties::inert() const
{
    return inert_;
}


AFC::wordList AFC::Properties::speciesOxidizer() const
{
    return speciesOxidizer_;
}


AFC::map<AFC::word, AFC::map<AFC::word, unsigned int>>
AFC::Properties::oxidizerA() const
{
    return oxidizerA_;
}


AFC::map<AFC::word, AFC::scalar> AFC::Properties::oxidizerX() const
{
    return oxidizerX_;
}


AFC::map<AFC::word, AFC::scalar> AFC::Properties::oxidizerY() const
{
    return oxidizerY_;
}


AFC::map<AFC::word, AFC::scalar> AFC::Properties::oxidizerZj() const
{
    return fuelZj_;
}


AFC::scalar AFC::Properties::oxidizerX(const word species) const
{
    return oxidizerX_.at(species);
}


AFC::scalar AFC::Properties::oxidizerY(const word species) const
{
    return oxidizerY_.at(species);
}


AFC::wordList AFC::Properties::speciesFuel() const
{
    return speciesFuel_;
}


AFC::map<AFC::word, AFC::map<AFC::word, unsigned int>>
AFC::Properties::fuelA() const
{
    return fuelA_;
}


AFC::map<AFC::word, AFC::scalar> AFC::Properties::fuelX() const
{
    return fuelX_;
}


AFC::map<AFC::word, AFC::scalar> AFC::Properties::fuelY() const
{
    return fuelY_;
}


AFC::map<AFC::word, AFC::scalar> AFC::Properties::fuelZj() const
{
    return fuelZj_;
}


AFC::scalar AFC::Properties::fuelX(const word species) const
{
    return fuelX_.at(species);
}


AFC::scalar AFC::Properties::fuelY(const word species) const
{
    return fuelY_.at(species);
}


AFC::scalarField AFC::Properties::defects() const
{
    return defects_;
}


AFC::scalar AFC::Properties::sDRs(const int i) const
{
    return sDRs_[i];
}


AFC::scalarField AFC::Properties::sDRs() const
{
    return sDRs_;
}


int AFC::Properties::nZPoints() const
{
    return nZPoints_;
}


int AFC::Properties::nZvarPoints() const
{
    return nZvarPoints_;
}


AFC::scalar AFC::Properties::oxidizerTemperature() const
{
    return TOxidizer_;
}


AFC::scalar AFC::Properties::fuelTemperature() const
{
    return TFuel_;
}


unsigned int AFC::Properties::nDefects() const
{
    return defects_.size();
}


AFC::scalar AFC::Properties::defect
(
    const int defectNo
) const
{
    return defects_[defectNo];
}


AFC::scalar AFC::Properties::p() const
{
    return p_;
}


AFC::word AFC::Properties::input() const
{
    if
    (
        !inputMol_
     && !inputMass_
    )
    {
        ErrorMsg
        (
            "Input problems for mass or mol fraction",
            __FILE__,
            __LINE__
        );
    }

    word input{"none"};

    if (inputMol_)
    {
        input = "mol";
    }
    else if (inputMass_)
    {
        input = "mass";
    }

    return input;
}


AFC::word AFC::Properties::interpreter() const
{
    return interpreter_;
}


AFC::scalar AFC::Properties::Zst() const
{
    return Zst_;
}


AFC::scalar AFC::Properties::YatZstu(const word species) const
{
    return YatZstu_.at(species);
}


AFC::scalar AFC::Properties::YatZstb(const word species) const
{
    return YatZstb_.at(species);
}


AFC::map<AFC::word, AFC::scalar> AFC::Properties::YatZstu() const
{
    return YatZstu_;
}

AFC::map<AFC::word, AFC::scalar> AFC::Properties::YatZstb() const
{
    return YatZstb_;
}


AFC::scalar AFC::Properties::adiabateFlameTemperature() const
{
    return PropertiesCalc::adiabateFlameTemperature
        (
            *this,
            thermo_,
            chemistry_  
        );
}


// * * * * * * * * * * * * * * Summary Function  * * * * * * * * * * * * * * //

void AFC::Properties::summary(ostream& data) const
{
    //- Header
    data<< Header() << "\n"; 

    data<< " c-o Properties summary (analysis of afcDict):\n"
        << " =============================================\n\n\n"
        << " =============================================================="
        << "===============\n"
        << " c-o Oxidizer information\n"
        << " =============================================================="
        << "===============\n"
        << "  |\n"
        << "  |--> Number of species:    " << speciesOxidizer_.size() << "\n"
        << "  |--> Oxidizer set to be:   " << oxidizer_ << "\n"
        << "  | \n"
        << "  | "
        << std::setw(15) << "Species"
        << std::setw(20) << "Mass Fraction"
        << std::setw(20) << "Mole Fraction"
        << std::setw(20) << "Concentration\n"
        << "  | " 
        << std::setw(35) << " Y [-]"
        << std::setw(20) << " X [-]"
        << std::setw(20) << " C [g/mol]\n" 
        << "  |------------------------------------------------------------"
        << "---------------\n";

    scalar sumY{0};
    scalar sumX{0};
    forAll(speciesOxidizer_, species)
    {
        data<< "  | " << std::right << std::setw(15) << species; 
        data<< std::setw(20) << oxidizerY_.at(species);
        data<< std::setw(20) << oxidizerX_.at(species);
        //data<< std::setw(20) << oxidizerN_.at(species);
        data<< "\n";

        sumY += oxidizerY_.at(species);
        sumX += oxidizerX_.at(species);
    }

    data<< "  |------------------------------------------------------------"
        << "---------------\n"
        << "  | "<< std::setw(15) << "Sum"
        << std::setw(20) << sumY
        << std::setw(20) << sumX
        << std::setw(20) << "\n"
        << "  |------------------------------------------------------------"
        << "---------------\n";

    loopMap(element, value, oxidizerZj_)
    {
        data<< "  | " << std::right << std::setw(15) << element; 
        data<< std::setw(20) << value;
        data<< std::setw(20) << oxidizerWj_.at(element);
        //data<< std::setw(20) << oxidizerN_.at(species);
        data<< "\n";
    }

    data<< "  |------------------------------------------------------------"
        << "---------------\n";

    data<< "\n\n"
        << " =============================================================="
        << "===============\n"
        << " c-o Fuel information\n"
        << " =============================================================="
        << "===============\n"
        << "  |\n"
        << "  |--> Number of species:    " << speciesFuel_.size() << "\n"
        << "  |--> Fuel set to be:       " << fuel_ << "\n"
        << "  | \n"
        << "  |------------------------------------------------------------"
        << "---------------\n"
        << "  | "
        << std::setw(15) << "Species"
        << std::setw(20) << "Mass Fraction"
        << std::setw(20) << "Mole Fraction"
        << std::setw(20) << "Concentration\n"
        << "  | " 
        << std::setw(35) << " Y [-]"
        << std::setw(20) << " X [-]"
        << std::setw(20) << " C [g/mol]\n" 
        << "  |------------------------------------------------------------"
        << "---------------\n";

    sumY = 0;
    sumX = 0;
    forAll(speciesFuel_, species)
    {
        data<< "  | " << std::right << std::setw(15) << species; 
        data<< std::setw(20) << fuelY_.at(species);
        data<< std::setw(20) << fuelX_.at(species);
        //data<< std::setw(20) << oxidizerN_.at(species);
        data<< "\n";

        sumY += fuelY_.at(species);
        sumX += fuelX_.at(species);
    }

    data<< "  |------------------------------------------------------------"
        << "---------------\n"
        << "  | "<< std::setw(15) << "Sum"
        << std::setw(20) << sumY
        << std::setw(20) << sumX
        << std::setw(20) << "\n"
        << "  |------------------------------------------------------------"
        << "---------------\n";

    loopMap(element, value, fuelZj_)
    {
        data<< "  | " << std::right << std::setw(15) << element; 
        data<< std::setw(20) << value;
        data<< std::setw(20) << fuelWj_.at(element);
        //data<< std::setw(20) << oxidizerN_.at(species);
        data<< "\n";
    }

    data<< "  |------------------------------------------------------------"
        << "---------------\n";
}
*/

// ************************************************************************* //
