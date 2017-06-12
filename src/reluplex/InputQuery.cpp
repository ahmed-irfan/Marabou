/*********************                                                        */
/*! \file InputQuery.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Guy Katz
 ** This file is part of the Reluplex project.
 ** Copyright (c) 2016-2017 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved. See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **/

#include "Stringf.h"
#include "InputQuery.h"
#include "ReluplexError.h"

#include <cfloat>

InputQuery::Equation::Addend::Addend( double coefficient, unsigned variable )
    : _coefficient( coefficient )
    , _variable( variable )
{
}

void InputQuery::Equation::addAddend( double coefficient, unsigned variable )
{
    _addends.append( Addend( coefficient, variable ) );
}

void InputQuery::Equation::setScalar( double scalar )
{
    _scalar = scalar;
}

InputQuery::InputQuery()
{
}

InputQuery::~InputQuery()
{
}

void InputQuery::setNumberOfVariables( unsigned numberOfVariables )
{
    _numberOfVariables = numberOfVariables;
}

void InputQuery::setLowerBound( unsigned variable, double bound )
{
    if ( variable >= _numberOfVariables )
    {
        throw ReluplexError( ReluplexError::VARIABLE_INDEX_OUT_OF_RANGE,
                             Stringf( "Variable = %u, number of variables = %u (setLowerBound)",
                                      variable, _numberOfVariables ).ascii() );
    }

    _lowerBounds[variable] = bound;
}

void InputQuery::setUpperBound( unsigned variable, double bound )
{
    if ( variable >= _numberOfVariables )
    {
        throw ReluplexError( ReluplexError::VARIABLE_INDEX_OUT_OF_RANGE,
                             Stringf( "Variable = %u, number of variables = %u (setUpperBound)",
                                      variable, _numberOfVariables ).ascii() );
    }

    _upperBounds[variable] = bound;
}

void InputQuery::addEquation( const Equation &equation )
{
    _equations.append( equation );
}

double InputQuery::getNumberOfVariables() const
{
    return _numberOfVariables;
}

double InputQuery::getLowerBound( unsigned variable ) const
{
    if ( variable >= _numberOfVariables )
    {
        throw ReluplexError( ReluplexError::VARIABLE_INDEX_OUT_OF_RANGE,
                             Stringf( "Variable = %u, number of variables = %u (getLowerBound)",
                                      variable, _numberOfVariables ).ascii() );
    }

    if ( !_lowerBounds.exists( variable ) )
        return -DBL_MAX;

    return _lowerBounds.get( variable );
}

double InputQuery::getUpperBound( unsigned variable ) const
{
    if ( variable >= _numberOfVariables )
    {
        throw ReluplexError( ReluplexError::VARIABLE_INDEX_OUT_OF_RANGE,
                             Stringf( "Variable = %u, number of variables = %u (getUpperBound)",
                                      variable, _numberOfVariables ).ascii() );
    }

    if ( !_upperBounds.exists( variable ) )
        return DBL_MAX;

    return _upperBounds.get( variable );
}

//
// Local Variables:
// compile-command: "make -C .. "
// tags-file-name: "../TAGS"
// c-basic-offset: 4
// End:
//