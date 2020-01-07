#pragma once

#include <string>

#include "envoy/access_log/access_log.h"
#include "envoy/config/typed_config.h"
#include "envoy/server/filter_config.h"

#include "common/protobuf/protobuf.h"

namespace Envoy {
namespace Server {
namespace Configuration {

/**
 * Implemented for each AccessLog::Instance and registered via Registry::registerFactory or the
 * convenience class RegisterFactory.
 */
class AccessLogInstanceFactory : public Config::TypedFactory {
public:
  virtual ~AccessLogInstanceFactory() = default;

  /**
   * Create a particular AccessLog::Instance implementation from a config proto. If the
   * implementation is unable to produce a factory with the provided parameters, it should throw an
   * EnvoyException. The returned pointer should never be nullptr.
   * @param config the custom configuration for this access log type.
   * @param filter filter to determine whether a particular request should be logged. If no filter
   * was specified in the configuration, argument will be nullptr.
   * @param context general filter context through which persistent resources can be accessed.
   */
  virtual AccessLog::InstanceSharedPtr createAccessLogInstance(const Protobuf::Message& config,
                                                               AccessLog::FilterPtr&& filter,
                                                               FactoryContext& context) PURE;

  std::string category() const override {
    static const char FACTORY_CATEGORY[] = "access_loggers";
    return FACTORY_CATEGORY;
  }
};

} // namespace Configuration
} // namespace Server
} // namespace Envoy
