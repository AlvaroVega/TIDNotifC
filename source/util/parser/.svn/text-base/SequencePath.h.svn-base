/*
 *  File name: SequencePath.h
 *  File type: Header file.
 *  Date : 13th February 2006
 *  Author: Alvaro Polo Valdenebro <apoloval@gsyc.escet.urjc.es>
 */

/*
// (C) Copyright 2009 Telefonica Investigacion y Desarrollo
 *
//     S.A.Unipersonal (Telefonica I+D)
//
 * by its owner.
 */

/*
 * Revision historial:
 *   - 02/14/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *      * SimpleNode inheritance was forgotten. Fixed.
 *      * New exception class BadTypeException. It's used in 
 *        'extract_from_dynany' method to indicate a invalid type check.
 *   - 03/07/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *      * Revision historial cleaned.
 *      * Parent class set to 'EvaluableNode' instead of 'SimpleNode'.
 *      * Method 'evaluate' implemented.
 *      * New method: 'extract_sequence_from_dynany'.
 *   - 23/10/2008, by Alvaro Vega Garcia <avega at tid dot es>:
 *       * Removed unnecessary _var templates in declarations
 */

#ifndef _TIDUTIL_SEQUENCEPATH_H
#define _TIDUTIL_SEQUENCEPATH_H

#include <DynamicAny.h>

#include "EvaluableNode.h"
#include "TypeValuePair.h"

namespace TIDNotif {
namespace util {
namespace parser{

class BadTypeException{};

/*!
 *
 * \brief Sequence path class for 'in' expressions.
 *
 * This class represents a complex expression to be found in
 * a value passed to a 'in' filter operation. It's formed by
 * a chain of steps (or sequence path), wich each one defines
 * a partial way to an object stored in a complex expression.
 * For instance, an element stored in an array stored in a
 * struct stored in a union, represented by filter expression
 * '$.("union_switch_value").field_name[7]' is represented by
 * a sequence like:
 *
 *   UnionStringSwitchPath --> StructFieldNamePath -->
 *   --> ArrayPath --> NULL
 */
class SequencePath : public EvaluableNode
{

  public:

    /*!
     * \brief Default constructor.
     * \param next_step Next step in sequence path.
     */
    SequencePath(SequencePath * next_step);

    /*!
     * \brief Destructor.
     *
     * This destructor will delete all chain components 
     * of sequence path.
     *
     */
    ~SequencePath();

    /*!
     * \brief Evaluate an object in a filter expression.
     * \param dynany Object to be evaluated.
     * \return Evaluation result.
     */
    virtual TypeValuePair evaluate(DynamicAny::DynAny_ptr dynany) const;

    /*!
     * \brief Evaluate 'in' operation.
     * \param simple_value Simple value to be found in the expression
     * represented by this sequence path.
     * \param dyn_any Expression value to be type-checked with this
     * sequence path.
     */
    TypeValuePair evaluate_in_operation(const TypeValuePair & simple_value,
                                        const DynamicAny::DynAny_ptr& dyn_any) const;

    /*!
     * \brief Extract associated value from a Dynamic Any.
     *
     * Extract a value for this sequence step from a dynamic any.
     *
     * \param from Source dynamic any to be value-extracted.
     * \param value Value extracted from source.
     */
    virtual void extract_from_dynany(const DynamicAny::DynAny_ptr& from,
                                     DynamicAny::DynAny_ptr & value) const
      throw (BadTypeException) = 0;

    /*!
     * \brief Extract associated value from a Dynamic Any for all sequence.
     *
     * Extract a value for all sequence from a dynamic any.
     *
     * \param from Source dynamic any to be value-extracted.
     * \param value Value extracted from source.
     */
    void extract_sequence_from_dynany(const DynamicAny::DynAny_ptr & from,
                                      DynamicAny::DynAny_ptr& value) const
      throw (BadTypeException);

  protected:

    /*!
     * \brief Next step protected field.
     */
    SequencePath * m_next_step;
    
  private:

    static char * __m_type_mismatch_msg;

};

} /* End of namespace parser.  */
} /* End of namespace util. */
} /* End of namespace TIDNotif.  */

#endif
