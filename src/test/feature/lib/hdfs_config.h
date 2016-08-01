#ifndef HAWQ_SRC_TEST_FEATURE_LIB_HDFS_CONFIG_H_
#define HAWQ_SRC_TEST_FEATURE_LIB_HDFS_CONFIG_H_

#include <string>
#include <vector>

#include "psql.h"
#include "sql_util.h"
#include "xml_parser.h"

namespace hawq {
namespace test {

/**
 * HdfsConfig common libray. Get detailed information about HDFS
 * including checking state of namenodes and datanodes, get parameter value
 * @author Chunling Wang
 */
class HdfsConfig {
  public:
    /**
     * HdfsConfig constructor
     */
    HdfsConfig(): psql(HAWQ_DB, HAWQ_HOST, HAWQ_PORT, HAWQ_USER, HAWQ_PASSWORD) {}

    /**
     * HdfsConfig desstructor
     */
    ~HdfsConfig() {}

    /**
     * whether HDFS is in HA mode
     * @return true if HDFS is HA
     */
    bool isHA();

    /**
     * whether HDFS is kerbos
     * @return true if HDFS is kerbos
     */
    bool isKerbos();

    /**
     * whether HDFS supports truncate operation
     * @return true if HDFS supports truncate operation
     */
    bool isTruncate();

    /**
     * get HADOOP working directory
     * @return HADOOP working directory
     */
    std::string getHadoopHome();

    /**
     * get HDFS active namenode's hostname and port information
     * @param activenamenode, active namenode hostname reference which will be set
     * @param port, active namenode port reference which will be set
     * @return true if getActiveNamenode succeeded
     */
    bool getActiveNamenode(std::string &activenamenode,
                           int &port);

    /**
     * get HDFS standby namenode's hostname and port information
     * @param standbynamenode, standby namenode hostname reference which will be set
     * @param port, standby namenode port reference which will be set
     * @return true if getStandbyNamenode succeeded
     */
    bool getStandbyNamenode(std::string &standbynamenode,
                            int &port);

    /**
     * get HDFS namenode(s) information
     * @param namenodes, namenodes' hostnames reference which will be set
     * @param port, namenodes' ports reference which will be set
     */
    void getNamenodes(std::vector<std::string> &namenodes,
                      std::vector<int> &port);

    /**
     * get HDFS datanodes information
     * @param datanodelist, datanodes' hostnames reference which will be set
     * @param port, datanodes' ports reference which will be set
     */
    void getDatanodelist(std::vector<std::string> &datanodelist,
                         std::vector<int> &port);

    /**
     * get HDFS active datanodes information
     * @param activedatanodes, active datanodes' hostnames reference which will be set
     * @param port, active datanodes' ports reference which will be set
     */
    void getActiveDatanodes(std::vector<std::string> &activedatanodes,
                            std::vector<int> &port);

    /**
     * whether HDFS is in safe mode
     * @return true if HDFS is in safe node
     */
    bool isSafemode();

    /**
     * get parameter value in ./etc/hdfs-client.xml or ./etc/hadoop/hdfs-site.xml according to parameter name
     * @param parameterName, used to get parameter value
     * @param conftype, get parameter value, 'hdfs' or 'HDFS' from ./etc/hdfs-client.xml, others from ./etc/hadoop/hdfs-site.xml
     * @return parameter value
     */
    std::string getParameterValue(const std::string &parameterName, const std::string &conftype);
    
    /**
     * get parameter value in ./etc/hadoop/hdfs-site.xml according to parameter name
     * @param parameterName, used to get parameter value
     * @return parameter value
     */
    std::string getParameterValue(const std::string &parameterName);

    /**
     * set parameter value in ./etc/hdfs-client.xml or ./etc/hadoop/hdfs-site.xml according to parameter name
     * @param parameterName, parameter name which used to set parameter value
     * @param parameterValue, parameter value which to be set
     * @param conftype, get parameter value, 'hdfs' or 'HDFS' from ./etc/hdfs-client.xml, others from ./etc/hadoop/hdfs-site.xml
     * @return true if succeeded
     */
    bool setParameterValue(const std::string &parameterName, const std::string &parameterValue, const std::string &conftype);

    /**
     * set parameter value in ./etc/hadoop/hdfs-site.xml according to parameter name
     * @param parameterName, parameter name which used to set parameter value
     * @param parameterValue, parameter value which to be set
     * @return true if succeeded
     */
    bool setParameterValue(const std::string &parameterName, const std::string &parameterValue);

  private:
    /**
     * @return yarn user
     */
    std::string getHdfsUser();
    /**
     * load key-value parameters in ./etc/hdfs-client.xml
     * @return true if succeeded
     */
    bool LoadFromHawqConfigFile();

    /**
     * load key-value parameters in ./etc/hadoop/hdfs-site.xml
     * @return true if succeeded
     */
    bool LoadFromHdfsConfigFile();

    /**
     * get HDFS active or standby namenode information in HA mode according to the namenodetype
     * @param namenodetype, used to specify active or standby namenode information
     * @param namenode, namenode hostname reference which will be set
     * @param port, namenode port reference which will be set
     * @return true if getHANamenode succeeded
     */
    bool getHANamenode(const std::string &namenodetype,
                       std::string &namenode,
                                   int &port);

  private:
    std::unique_ptr<XmlConfig> hawqxmlconf;
    std::unique_ptr<XmlConfig> hdfsxmlconf;
    hawq::test::PSQL psql;
};

} // namespace test
} // namespace hawq

#endif /* HAWQ_SRC_TEST_FEATURE_LIB_HDFS_CONFIG_H_ */
