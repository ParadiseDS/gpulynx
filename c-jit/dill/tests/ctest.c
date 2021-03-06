#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dill.h"

int main(int argc, char **argv) 
{ 
    dill_reg r;
    int i;
    dill_stream c = dill_create_raw_stream();
    dill_exec_handle h;
    void (*func)();
    int verbose = 0, no_float = 0;

    for (i=1; i < argc; i++) {
	if (strcmp(argv[i], "-no_float") == 0) {
	    no_float++;
	} else if (strcmp(argv[i], "-v") == 0) {
	    verbose++;
	}
    }

    dill_start_simple_proc(c, "foo", DILL_V);
    dill_raw_getreg(c, &r, DILL_I, DILL_TEMP);
	
    dill_push_init(c);
    if (!dill_do_reverse_vararg_push(c)) {
	dill_push_argpi(c, "Hello: %d %d %d %d\n");
	dill_seti(c, r, 10);
	dill_push_argi(c, r);
	dill_seti(c, r,20);
	dill_push_argi(c, r);
	dill_seti(c, r,30);
	dill_push_argi(c, r);
	dill_seti(c, r,40);
	dill_push_argi(c, r);
    } else {
	dill_seti(c, r,40);
	dill_push_argi(c, r);
	dill_seti(c, r,30);
	dill_push_argi(c, r);
	dill_seti(c, r,20);
	dill_push_argi(c, r);
	dill_seti(c, r, 10);
	dill_push_argi(c, r);
	dill_push_argpi(c, "Hello: %d %d %d %d\n");
    }
    dill_callv(c, (void*)printf, "printf");
    h = dill_finalize(c);
    func = (void (*)())dill_get_fp(h);
    if (verbose) dill_dump(c);
    func();
    dill_free_handle(h);

    dill_start_simple_proc(c, "foo", DILL_V);
    dill_push_init(c);
    if (!dill_do_reverse_vararg_push(c)) {
	dill_push_argpi(c, "Hello: %d %d %d %d\n");
	dill_push_argii(c, 10);
	dill_push_argii(c, 20);
	dill_push_argii(c, 30);
	dill_push_argii(c, 40);
    } else {
	dill_push_argii(c, 40);
	dill_push_argii(c, 30);
	dill_push_argii(c, 20);
	dill_push_argii(c, 10);
	dill_push_argpi(c, "Hello: %d %d %d %d\n");
    }
    dill_callv(c, (void*)printf, "printf");
    h = dill_finalize(c);
    func = (void (*)()) dill_get_fp(h);
    if (verbose) dill_dump(c);
    func();
    dill_free_handle(h);

    dill_start_simple_proc(c, "foo", DILL_V);
    dill_push_init(c);
    if (!dill_do_reverse_vararg_push(c)) {
	dill_push_argpi(c, "Hello: %d %d %d %d %d %d %d %d %d %d\n");
	dill_push_argii(c, 10);
	dill_push_argii(c, 20);
	dill_push_argii(c, 30);
	dill_push_argii(c, 40);
	dill_push_argii(c, 50);
	dill_push_argii(c, 60);
	dill_push_argii(c, 70);
	dill_push_argii(c, 80);
	dill_push_argii(c, 90);
	dill_push_argii(c, 100);
    } else {
	dill_push_argii(c, 100);
	dill_push_argii(c, 90);
	dill_push_argii(c, 80);
	dill_push_argii(c, 70);
	dill_push_argii(c, 60);
	dill_push_argii(c, 50);
	dill_push_argii(c, 40);
	dill_push_argii(c, 30);
	dill_push_argii(c, 20);
	dill_push_argii(c, 10);
	dill_push_argpi(c, "Hello: %d %d %d %d %d %d %d %d %d %d\n");
    }
    dill_callv(c, (void*)printf, "printf");
    h = dill_finalize(c);
    func = (void (*)())dill_get_fp(h);
    if (verbose) dill_dump(c);
    func();
    dill_free_handle(h);

    if (!no_float) {
	dill_start_simple_proc(c, "foo", DILL_V);
	dill_push_init(c);
	if (!dill_do_reverse_vararg_push(c)) {
	    dill_push_argpi(c, "Hello: %e %e %e %e %e %e %e %e %e %e\n");
	    dill_push_argdi(c, 10.0);
	    dill_push_argdi(c, 20.0);
	    dill_push_argdi(c, 30.0);
	    dill_push_argdi(c, 40.0);
	    dill_push_argdi(c, 50.0);
	    dill_push_argdi(c, 60.0);
	    dill_push_argdi(c, 70.0);
	    dill_push_argdi(c, 80.0);
	    dill_push_argdi(c, 90.0);
	    dill_push_argdi(c, 100.0);
	} else {
	    dill_push_argdi(c, 100.0);
	    dill_push_argdi(c, 90.0);
	    dill_push_argdi(c, 80.0);
	    dill_push_argdi(c, 70.0);
	    dill_push_argdi(c, 60.0);
	    dill_push_argdi(c, 50.0);
	    dill_push_argdi(c, 40.0);
	    dill_push_argdi(c, 30.0);
	    dill_push_argdi(c, 20.0);
	    dill_push_argdi(c, 10.0);
	    dill_push_argpi(c, "Hello: %e %e %e %e %e %e %e %e %e %e\n");
	}
	dill_callv(c, (void*)printf, "printf");
	h = dill_finalize(c);
	func = (void (*)())dill_get_fp(h);
	if (verbose) dill_dump(c);
	func();
	dill_free_handle(h);
    } else {
	/* just do the printf so the output is the same */
	printf("Hello: %e %e %e %e %e %e %e %e %e %e\n", 10.0, 20.0, 30.0, 
	       40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0);
    }
    return 0;
}
