#ifndef NET_PACKAGE_H_
#define NET_PACKAGE_H_
#include <string>
#include <cstdint>
#include <vector>
#include <memory>

class NetPackage
{
public:
	static std::string extract_string(int8_t *data_src, size_t _size);
	static std::string extract_string(const std::vector<int8_t> &data_src, size_t index1, size_t _size);
	template<class InputIterator>
	static std::string extract_string(InputIterator first, InputIterator last);
	template<class InputIterator>
	static std::vector<int8_t> pack_string(InputIterator first, InputIterator last);
	enum class PackType:uint32_t {UNKN, OK, CONFIRM_OK, READY, REQ_RUNDIR, RUNDIR, REQ_LINPACK, LINPACK, CMD, 
		START_RUN, RUN_FINISHED, RUN_FAILED, RUN_KILLED, TERMINATE,PING,REQ_KILL,IO_ERROR};
	static int get_new_group_id();
	NetPackage(PackType _type=PackType::UNKN, int _group=-1, int _run_id=-1, const std::string &desc="");
	~NetPackage(){}
	const static int DESC_LEN = 41;
	int send(int sockfd, const void *data, int64_t data_len_l);
	int recv(int sockfd);
	void reset(PackType _type, int _group, int _run_id, const std::string &_desc);
	PackType get_type() const {return type;}
	int64_t get_run_id() const { return run_id; }
	int64_t get_group_id() const { return group; }
	const std::vector<int8_t> &get_data(){ return data; }
	void print_header(std::ostream &fout);
	

private:
	int64_t data_len;
	static int64_t last_group_id;
	PackType type;
	int64_t group;
	int64_t run_id;
	int8_t desc[DESC_LEN];
	std::vector<int8_t> data;
};

#endif /* NET_PACKAGE_H_ */
