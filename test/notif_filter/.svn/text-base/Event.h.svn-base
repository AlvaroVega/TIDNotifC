// Event.h
//
// File generated: Mon May 22 09:43:25 CEST 2006
//   by TIDIdlc idl2cpp 1.2.2
//

#ifndef __EVENT_H_
#define __EVENT_H_

#include "TIDorb/portable.h"

#include "TIDorb/types.h"

#include "CORBA.h"
//
// Events.h (module)
//
// File generated: Mon May 22 09:43:25 CEST 2006
//   by TIDIdlc idl2cpp 1.2.2
//






namespace Events
{
	// Begin of forward Declarations  definition
		class Test_Event;
		typedef Test_Event* Test_Event_ptr;
		typedef ::TIDorb::templates::FixedSizeT_var<Test_Event> Test_Event_var;
		typedef Test_Event &Test_Event_out;
	// End of forward declarations


	// Begin of children  header files inclusion
//
// Test_Event.h (struct)
//
// File generated: Mon May 22 09:43:25 CEST 2006
//   by TIDIdlc idl2cpp 1.2.2
//



extern const ::CORBA::TypeCode_ptr _tc_Test_Event;

class  Test_Event
{

public:
		typedef Test_Event_var  _var_type;


		// Member Attributes.   

		CORBA::Long campo_uno;
		CORBA::Long campo_dos;
		CORBA::Long campo_tres;

		// Member Functions.   

		Test_Event(); /*Empty Constructor */ 

		Test_Event(const Test_Event&);

		Test_Event(CORBA::Long pcampo_uno, CORBA::Long pcampo_dos, CORBA::Long pcampo_tres);
}; // End of class for struct Test_Event
class _Test_EventHelper {

	public:
		static ::CORBA::TypeCode_ptr type();

		static const char* id() { return "IDL:Events/Test_Event:1.0"; }

		static void insert(::CORBA::Any& any, const Events::Test_Event& _value);

		static void insert(::CORBA::Any& any, Events::Test_Event* _value);

		static CORBA::Boolean extract(const ::CORBA::Any& any, const Events::Test_Event*& _value);

		static void read(::TIDorb::portable::InputStream& is, Events::Test_Event& _value);

		static void write(::TIDorb::portable::OutputStream& os, const Events::Test_Event& _value);

};// End of helper definition

class _Test_EventHolder: public virtual ::TIDorb::portable::Streamable {

		public:
		Events::Test_Event* value; 

		_Test_EventHolder() {value = NULL;}
		_Test_EventHolder(const Events::Test_Event& initial){
			value = new Events::Test_Event(initial);
		}
		~_Test_EventHolder() {delete value;}
		_Test_EventHolder& operator= (const _Test_EventHolder& other) {
			if (value) delete value;
			value = new Events::Test_Event(*(other.value));
			return *this;
		}
		::CORBA::TypeCode_ptr _type() const;
		void _write(::TIDorb::portable::OutputStream& outs) const
		{
			Events::_Test_EventHelper::write(outs,*value); 
		}
		void _read(::TIDorb::portable::InputStream& ins) 
		{
			if (!value) value = new Events::Test_Event();
			Events::_Test_EventHelper::read(ins, *value); 
		}
}; // end of holder class COMPLEX




	// End of children  header files inclusion

}// end of namespace Events

//
// Events_ext.h (from module)
//
// File generated: Mon May 22 09:43:25 CEST 2006
//   by TIDorb idl2cpp 1.2.2
//   external Any operators definition File.//



//
// Test_Event_ext.h (from struct)
//
// File generated: Mon May 22 09:43:25 CEST 2006
//   by TIDorb idl2cpp 1.2.2
//   external Any operators definition File.//



		inline void operator <<= (::CORBA::Any& any, const Events::Test_Event& _value)
		{
			Events::_Test_EventHelper::insert(any,_value);
		}
		inline void operator <<= (::CORBA::Any& any, Events::Test_Event* _value)
		{
			Events::_Test_EventHelper::insert(any,_value);
		}
		inline CORBA::Boolean operator >>= (const ::CORBA::Any& any, const Events::Test_Event*& _value)
		{
			return Events::_Test_EventHelper::extract(any, _value);
		}






#endif // __EVENT_H_
