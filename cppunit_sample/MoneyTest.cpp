//#include "stdafx.h"
#include "MoneyTest.h"
#include "Money.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( MoneyTest );


void 
MoneyTest::setUp()
{
}


void 
MoneyTest::tearDown()
{
}


void 
MoneyTest::testConstructor()
{
  // Set up
  const std::string currencyFF( "FF" );
  const double longNumber = 12345678.90123;

  // Process
  Money money( longNumber, currencyFF );

  // Check
  CPPUNIT_ASSERT_EQUAL( longNumber, money.getAmount() );
  CPPUNIT_ASSERT_EQUAL( currencyFF, money.getCurrency() );
}

void
MoneyTest::testEqual()
{
  // Set up
  const Money money123FF( 123, "FF" );
  const Money money123USD( 123, "USD" );
  const Money money12FF( 12, "FF" );
  const Money money12USD( 12, "USD" );

  // Process & Check
  CPPUNIT_ASSERT( money123FF == money123FF );     // ==
  CPPUNIT_ASSERT( money12FF != money123FF );      // != amount
  CPPUNIT_ASSERT( money123USD != money123FF );    // != currency
  CPPUNIT_ASSERT( money12USD != money123FF );     // != currency and != amount
}

void 
MoneyTest::testAdd()
{
  // Set up
  const Money money12FF( 12, "FF" );
  const Money expectedMoney( 135, "FF" );

  // Process
  Money money( 123, "FF" );
  money += money12FF;

  // Check
  CPPUNIT_ASSERT( expectedMoney == money );           // add works
  CPPUNIT_ASSERT( &money == &(money += money12FF) );  // add returns ref. on 'this'.
}

void 
MoneyTest::testAddThrow()
{
  // Set up
  const Money money123FF( 123, "FF" );

  // Process
  Money money( 123, "USD" );
  bool expected_exception_thrown = false;
  try
  {
      money += money123FF;
  }
  catch(const IncompatibleMoneyError)
  {
      expected_exception_thrown = true;
  }
  if (!expected_exception_thrown)
      CPPUNIT_FAIL("Expected exception, did not get one");
}
