/*
 *  File name: SimpleNode.C
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
 *   - 02/14/20006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Code cleaning.
 *       * DynamicAnyFactory reference is traslated from class 
 *         TIDConstraint. All its childrens can use this reference 
 *         to obtain DynAny objects. In addiction, error is reported by
 *         DynAnyFactoryLocationErrorException instead of a int error code.
 *   - 03/31/20006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Exception raised in 'dump' must be throw without a new operator.
 *       * Added virtual destructor.
 *   - 16/06/2008, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Performance improvement: avoid to call to locateDynAnyFactory() if 
 *       * dynAnyFactory is not NULL
 *
 */

#include "SimpleNode.h"

namespace TIDNotif {
namespace util {
namespace parser {

/* DynAnyFactory internal class hierarchy reference. */
DynamicAny::DynAnyFactory_ptr SimpleNode::dynAnyFactory = NULL;

/* Default constructor. */
SimpleNode::SimpleNode()
{
  try
  {
    if (SimpleNode::dynAnyFactory == NULL)
    {
      locateDynAnyFactory();
    }
  }
  catch (DynAnyFactoryLocationErrorException & exc)
  {
    throw CORBA::INTERNAL("Cannot allocate dynamic any factory.");
  }
}

/* Destructor. */
SimpleNode::~SimpleNode()
{}

/* Override this method if you want to customize how the node dumps
     out its children. */
void SimpleNode::dump(string prefix){
  throw CORBA::NO_IMPLEMENT("No implemented");
}

/* Locate DynAnyFactory reference. */
void
SimpleNode::locateDynAnyFactory()
throw (DynAnyFactoryLocationErrorException)
{
  CORBA::ORB_var orb;
  char ** args;
  int i;
  const char * orb_id;
  CORBA::Object_ptr obj;


  try
  {
    i = 0;
    orb_id="TIDConstraint";
    orb = CORBA::ORB_init(i,args,orb_id);
  }
  catch (CORBA::Exception& e)
  {
    //TIDParser.printStackTrace(TIDParser.ERROR, e); //TODO_MORFEO: Trace.
    throw DynAnyFactoryLocationErrorException();
  }

  try
  {
    obj = orb->resolve_initial_references("DynAnyFactory");
    SimpleNode::dynAnyFactory = DynamicAny::_DynAnyFactoryHelper::narrow(obj,true);
  }
  catch (CORBA::Exception& e)
  {
    //TIDParser.printStackTrace(TIDParser.ERROR, e); //TODO_MORFEO: Trace.
    throw DynAnyFactoryLocationErrorException();
  }
}

}; /* End of namespace parser. */
}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */

