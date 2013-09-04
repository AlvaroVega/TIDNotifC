// Event.C
//
// File generated: Mon May 22 09:43:25 CEST 2006
//   by TIDIdlc idl2cpp 1.2.2
//

#include "Event.h"


//
// Test_Event.C (struct)
//
// File generated: Mon May 22 09:43:25 CEST 2006
//   by TIDIdlc idl2cpp 1.2.2
//


#include "TIDorb/portable/TypeCodeFactory.h" 

void Events::_Test_EventHelper::insert(::CORBA::Any& any, const Events::Test_Event& _value) {
	::TIDorb::portable::Any& delegate=any.delegate(); 
	delegate.insert_Streamable(new Events::_Test_EventHolder(_value));
}

void Events::_Test_EventHelper::insert(::CORBA::Any& any, Events::Test_Event* _value) {
	::TIDorb::portable::Any& delegate=any.delegate(); 
	delegate.insert_Streamable(new Events::_Test_EventHolder(*_value));
	delete _value;
}

CORBA::Boolean Events::_Test_EventHelper::extract(const ::CORBA::Any& any, const Events::Test_Event*& _value) {
	::TIDorb::portable::Any& delegate=any.delegate();
	const TIDorb::portable::Streamable* _holder;
	if(delegate.extract_Streamable(_holder))
	{
		const Events::_Test_EventHolder* _hld=dynamic_cast< const Events::_Test_EventHolder*>(_holder);
		if(_hld){
			(Events::Test_Event*&)_value = _hld->value;
			return true;
		} else { 
			return false;
		}
	} // has Streamable
	Events::_Test_EventHolder* _hld = new Events::_Test_EventHolder();
	try {
		CORBA::Boolean ret = delegate.set_Streamable(_hld);
		(Events::Test_Event*&)_value = _hld->value;
		if (!ret) delete _hld;
		return ret;
	} catch (CORBA::BAD_OPERATION _e) {
		delete _hld;
		return false;
	}
}

CORBA::TypeCode_ptr Events::_Test_EventHelper::type() {
	if (Events::_tc_Test_Event) {
		return Events::_tc_Test_Event;
	}

	CORBA::StructMemberSeq_ptr members = new ::CORBA::StructMemberSeq();
	members->length(3);
	(*members)[0].name = (::CORBA::Identifier) CORBA::string_dup("campo_uno");
	(*members)[0].type = TIDorb::portable::TypeCodeFactory::get_basic_TypeCode(::CORBA::tk_long);
	(*members)[0].type_def = CORBA::IDLType::_nil();
	(*members)[1].name = (::CORBA::Identifier) CORBA::string_dup("campo_dos");
	(*members)[1].type = TIDorb::portable::TypeCodeFactory::get_basic_TypeCode(::CORBA::tk_long);
	(*members)[1].type_def = CORBA::IDLType::_nil();
	(*members)[2].name = (::CORBA::Identifier) CORBA::string_dup("campo_tres");
	(*members)[2].type = TIDorb::portable::TypeCodeFactory::get_basic_TypeCode(::CORBA::tk_long);
	(*members)[2].type_def = CORBA::IDLType::_nil();
	return TIDorb::portable::TypeCodeFactory::create_struct_tc(
		(const ::CORBA::RepositoryId ) id(),(const ::CORBA::Identifier ) "Test_Event", members);
}

const ::CORBA::TypeCode_ptr Events::_tc_Test_Event=Events::_Test_EventHelper::type();

void Events::_Test_EventHelper::read(::TIDorb::portable::InputStream& is, Events::Test_Event& _value) {
	is.read_long(_value.campo_uno);
	is.read_long(_value.campo_dos);
	is.read_long(_value.campo_tres);
}

void Events::_Test_EventHelper::write(::TIDorb::portable::OutputStream& os, const Events::Test_Event& _value) {
	os.write_long(_value.campo_uno);
	os.write_long(_value.campo_dos);
	os.write_long(_value.campo_tres);
}

::CORBA::TypeCode_ptr Events::_Test_EventHolder::_type() const {
	return CORBA::TypeCode::_duplicate(Events::_Test_EventHelper::type());
}

/* Empty constructor */

Events::Test_Event::Test_Event()
{
}

/* Copy constructor */

Events::Test_Event::Test_Event(const Events::Test_Event& _s)
{
	campo_uno = _s.campo_uno;
	campo_dos = _s.campo_dos;
	campo_tres = _s.campo_tres;
}

/* Member constructor */

Events::Test_Event::Test_Event(CORBA::Long pcampo_uno, CORBA::Long pcampo_dos, CORBA::Long pcampo_tres) : campo_uno(pcampo_uno), campo_dos(pcampo_dos), campo_tres(pcampo_tres)
{
}


