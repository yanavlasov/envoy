cluster_format = r"""resources {
  [type.googleapis.com/envoy.config.cluster.v3.Cluster] {
    name: "%s"
    type: STATIC
    load_assignment {
      cluster_name: "%s"
      endpoints {
	lb_endpoints {
          endpoint {
            address {
              socket_address {
		address: "::1"
		port_value: 443
              }
            }
          }
	}
      }
    }
    connect_timeout {
      nanos: 100000000
    }
  }
}
"""

with open("cds_large.text", "w") as file:
    file.write("version_info: \"0\"\n")
    for i in range(10):
        cluster_name = "cluster_" + str(i)
        file.write(cluster_format % (cluster_name, cluster_name))
    file.write("type_url: \"type.googleapis.com/envoy.config.cluster.v3.Cluster\"\n")

print("Content successfully written to cds_large.pb_text")
