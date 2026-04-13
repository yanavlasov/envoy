#include "source/exe/main_common.h"

#ifdef WIN32
#include "source/exe/service_base.h"
#endif

#include "tcmalloc/malloc_extension.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#include "tcmalloc/static_vars.h"
#pragma clang diagnostic pop

// NOLINT(namespace-envoy)

/**
 * Basic Site-Specific main()
 *
 * This should be used to do setup tasks specific to a particular site's
 * deployment such as initializing signal handling. It calls main_common
 * after setting up command line options.
 */
int main(int argc, char** argv) {
  //tcmalloc::tcmalloc_internal::tc_globals.system_allocator().set_madvise_preference(tcmalloc::tcmalloc_internal::MadvisePreference::kFreeAndDontNeed);
  printf("----------------- %d\n", static_cast<int>(tcmalloc::tcmalloc_internal::tc_globals.system_allocator().madvise_preference()));
#ifdef WIN32
  Envoy::ServiceBase service;
  if (!Envoy::ServiceBase::TryRunAsService(service)) {
    return Envoy::MainCommon::main(argc, argv);
  }
  return EXIT_SUCCESS;
#endif
  return Envoy::MainCommon::main(argc, argv);
}
