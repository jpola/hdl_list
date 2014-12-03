#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "test_resources.h"
#include "hdl_list.h"


BOOST_AUTO_TEST_CASE(hdl_list_add)
{
    hdl_list* L = hdl_create(false);
    BOOST_CHECK(L != NULL);

    hdl_push_back(L, k1, source1);
    BOOST_CHECK_EQUAL(1, hdl_size(L));

    hdl_push_front(L, k2, source1);
    BOOST_CHECK_EQUAL(2, hdl_size(L));

    hdl_insert(L, k3, source3);
    BOOST_CHECK_EQUAL(3, hdl_size(L));

    hdl_destroy(&L);
    BOOST_CHECK(L == NULL);
}

BOOST_AUTO_TEST_CASE(hdl_list_add_duplicated)
{
    hdl_list* L = hdl_create(false);
    BOOST_CHECK(L != NULL);

    hdl_push_back(L, k1, source1);
    BOOST_CHECK_EQUAL(1, hdl_size(L));

    hdl_push_front(L, k2, source1);
    BOOST_CHECK_EQUAL(2, hdl_size(L));

    hdl_insert(L, k2, source2);
    BOOST_CHECK_EQUAL(2, hdl_size(L));

    hdl_destroy(&L);
    BOOST_CHECK(L == NULL);
}
