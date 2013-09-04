/*
 *  File name: SimpleNode.h
 *  File type: Header file.
 *  Date : January 2006
 *  Author: David Alonso <dalonso@gsyc.escet.urjc.es>
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
 *   - 02/14/20006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Code cleaning.
 *       * DynamicAnyFactory reference is traslated from class 
 *         TIDConstraint. All its childrens can use this reference 
 *         to obtain DynAny objects. In addiction, error is reported by
 *         DynAnyFactoryLocationErrorException instead of a int error code.
 *   - 03/31/20006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added virtual destructor.
 */

#ifndef _TIDUTIL_SIMPLENODE_H_
#define _TIDUTIL_SIMPLENODE_H_

#include <DynamicAny.h>
#include <CORBA.h>

namespace TIDNotif {
namespace util {
namespace parser {

/* SimpleNode class predefinition. */
class SimpleNode;

/*!
 * \brief SimpleNode pointer type.
 */
typedef SimpleNode * SimpleNode_ptr;

/*!
 * \brief DynAnyFactoryLocationErrorException.
 *
 * This exception is raised when DynAnyFactory reference
 * cannot be resolved.
 */
class DynAnyFactoryLocationErrorException {};

/*!
 * \brief Parser simple node class.
 *
 * This class represents a parser-tree node data.
 */
class SimpleNode
{

  public:

    /*!
     * \brief Default constructor.
     */
    SimpleNode();

    /*!
     * \brief Destructor.
     */
    virtual ~SimpleNode();

    void dump(string prefix);

  private:

    /*!
     * \brief Locate DynAnyFactory reference.
     * \throw DynAnyFactoryLocationErrorException This exception
     * will be raised if DynAnyFactory reference cannot be resolved.
     */
    virtual void locateDynAnyFactory() 
      throw (DynAnyFactoryLocationErrorException); //TODO_MORFEO: synchronized

  protected:

    /*!
     * \brief DynAnyFactory internal class hierarchy reference.
     */
    static DynamicAny::DynAnyFactory_ptr dynAnyFactory;

};

}; /* End of namespace parser. */
}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */

#endif
