/*
 *  File name: TIDConstraint.C
 *  File type: Body file.
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
 *   - 02/14/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Code cleaning.
 *       * DynamicAnyFactory reference is traslated to class SimpleNode.
 *         All its childrens can use this reference to obtain DynAny
 *         objects. In addiction, error is reported by
 *         DynAnyFactoryLocationErrorException instead of a int error code.
 *
 *   - 03/03/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Debugging messages inserted in code.
 *   - 03/07/2007, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * No root node debugging message.
 *   - 03/30/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Destructor implemented.
 *   - 03/31/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added code for allocated memory debugging purposes.
 *       * 'root' object must not be const.
 *   - 04/10/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * In 'check_event(...)', evaluation result type is check. If
 *         result is neither bool nor error type, an error is returned.
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 */

#include "TIDConstraint.h"
#include "Debugger.h"

namespace TIDNotif{
namespace util{
namespace parser{

/* Default constructor. */
TIDConstraint::TIDConstraint()
:
EvaluableNode(),
root(0)
{}

/* Root constructor. */
TIDConstraint::TIDConstraint(EvaluableNode * root_node)
:
EvaluableNode(),
root(root)
{}

/* Destructor. */
TIDConstraint::~TIDConstraint()
{
  if (root)
  {
    #ifdef DEBUG_ENABLED
    Debugger::register_free(root);
    #endif
    delete root;
  }
}

/* Evaluate an object in a filter expression. */
TypeValuePair
TIDConstraint::evaluate(DynamicAny::DynAny_ptr dynany) const
{
  if (root)
  {
    #ifdef DEBUG_ENABLED
    Debugger::send_message(70, 
      "Constraint object calling to evaluate on root node", this);
    #endif
    return root->evaluate(dynany);
  }
  else
  {
    #ifdef DEBUG_ENABLED
    Debugger::send_message(70, 
      "Warning: constraint has no root node!!!", this);
    #endif
    return TypeValuePair::create_error("constraint has no root node");
  }
}

/* Check if an event passes this filter. */
TypeValuePair
TIDConstraint::check_event(const CORBA::Any& event )
{
  DynamicAny::DynAny_ptr dynAny;
  string msg;

  try
  {
    dynAny = TIDConstraint::dynAnyFactory->create_dyn_any(event);
  }
  catch (CORBA::Exception& e)
  {
    //TIDParser.printStackTrace(TIDParser.ERROR, e); //TODO_MORFEO: Trace.
    return TypeValuePair::create_error(
      "error while creating DynAny from event");
  }
  TypeValuePair result = evaluate(dynAny);
  if (result.get_type() != TypeValuePair::BOOLEAN_TYPE &&
      result.get_type() != TypeValuePair::ERROR_TYPE)
  {
    #ifdef DEBUG_ENABLED
    Debugger::send_message(70, 
      "Check event produces a neither bool nor error value", this);
    #endif
    msg = "Event evaluation produces a unexpected value of type ";
    msg.append(result.get_type_image());
    CORBA::release(dynAny);
    return TypeValuePair::create_error(msg.c_str());
  }
  CORBA::release(dynAny);
  return result;
}

/* Add a root to this constraint. */
void
TIDConstraint::addRoot (EvaluableNode * r)
{
  root=r;
}

/* Copy this node. */
EvaluableNode *
TIDConstraint::copy() const
{
  TIDConstraint * node;

  node = new TIDConstraint(root->copy());
  #ifdef DEBUG_ENABLED
  util::parser::Debugger::register_malloc(node);
  #endif
  return node;
}

};
}; //namespace util
}; //namespace TIDNotif
