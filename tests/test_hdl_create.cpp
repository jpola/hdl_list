#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "test_resources.h"
#include "hdl_list.h"


BOOST_AUTO_TEST_CASE(hdl_list_create)
{
    hdl_list* L = NULL;
    L = hdl_create(false);

    BOOST_CHECK(L != NULL);

    hdl_insert(L, k1, source1);
    hdl_insert(L, k2, source2);
    hdl_insert(L, k3, source3);
    hdl_insert(L, k4, source4);

    hdl_destroy(&L);

    BOOST_CHECK(L == NULL);
}

BOOST_AUTO_TEST_CASE(hdl_list_destroy)
{
    hdl_list* L = NULL;
    L = hdl_create(false);
    hdl_destroy(&L);
    hdl_destroy(&L);

    BOOST_CHECK(L == NULL);

}
