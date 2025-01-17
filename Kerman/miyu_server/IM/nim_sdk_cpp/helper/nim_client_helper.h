﻿/** @file nim_client_helper.h
  * @brief Client 辅助方法和数据结构定义
  * @copyright (c) 2015-2017, NetEase Inc. All rights reserved
  * @date 2015/09/07
  */
#ifndef _NIM_SDK_CPP_CLIENT_HELPER_H_
#define _NIM_SDK_CPP_CLIENT_HELPER_H_

#include <string>
#include <list>
#include <functional>
#include "json.h"
#include "nim_base_types.h"
#include "nim_sdk_defines.h"
#include "nim_sdk_cpp_wrapper_dll.h"
/**
* @namespace nim
* @brief namespace nim
*/
namespace nim
{

/** @brief SDK设置项 */
 struct NIM_SDK_CPPWRAPPER_DLL_API SDKConfig
{
	//global_config
	std::string		database_encrypt_key_;			/**< 数据库秘钥，必填，目前只支持最多32个字符的加密密钥！建议使用32个字符 */
	bool			preload_attach_;				/**< 是否需要预下载附件(图片和语音),选填,默认为true,如果有对带宽流量有较高要求的请关闭该选项，改为上层开发者按需下载附件文件 */
	int				preload_image_quality_;			/**< 预下载图片质量,选填,范围0-100 */
	std::string		preload_image_resize_;			/**< 预下载图片基于长宽做内缩略,选填,比如宽100高50,则赋值为100x50,中间为字母小写x */
	std::string		preload_image_name_template_;/**< 预下载图片命名规则，以{filename}为token进行替换 */
	NIMSDKLogLevel	sdk_log_level_;					/**< 定义见NIMSDKLogLevel，选填，SDK默认的内置级别为kNIMSDKLogLevelPro */
	bool			sync_session_ack_;				/**< 设置是否已读未读状态多端同步，默认true */
	int				login_max_retry_times_;			/**< 登录重试最大次数，如需设置建议设置大于3次，默认填0，SDK默认设置次数 */
	int				custom_timeout_;				/**< 自定义通讯超时时间，暂时不开放设置 */
	bool			use_https_;						/**< 是否启用HTTPS协议，默认为false */
	bool			team_notification_unread_count_;/**< 群通知是否计入未读数，默认为false */
	bool			reset_unread_count_when_recall_;/**< 撤回消息是否重新计算未读消息计数，默认为false */
	bool			animated_image_thumbnail_enabled_;/**< 开启对动图缩略图的支持	，默认为false,开启后获取的缩略图为原格式，关闭后获取的缩略图为第一帧静态图 */
	bool			client_antispam_;				/**< 客户端反垃圾，默认为false，如需开启请提前咨询技术支持或销售 */
	bool			team_msg_ack_;					/**< 群消息已读功能开关， 默认为false，如需开启请提前咨询技术支持或销售  */
	/***********消息“已接收回执”发送配置 begin************/
	//bool		enable_markread_after_save_db_; /**< bool, 是否开启消保存在本地DB以后再向服务端发送"已接收回执" 缺省 false 关闭*/
	bool		caching_markread_; /**< 是否开启缓存式“已接收回执”发送，程序可能收到大量消息以至触发频控时可以考虑开启此开关 缺省 false 关闭*/
	uint32_t		caching_markread_time_; /**< caching_markread_ == true 时有效 缓存时间 单位ms 缺省 1000 */
	uint32_t		caching_markread_count_; /**< caching_markread_ == true 时有效 缓存的最大消息条数  缺省 10 */
	/***********消息“已接收回执”发送配置 end************/

	/***********用户数据本地备份与恢复 begin************/
	bool		enable_user_datafile_backup_; /**< bool 是否开启用户数据备份(本地)功能  缺省true*/
	bool		enable_user_datafile_restore_;  /**< bool 是否开启用户数据恢复(本地)功能  缺省false*/
	bool		enable_user_datafile_defrestoreproc_;  /**< bool 是否使用缺省的用户数据恢复(本地)方案  缺省false enable_user_datafile_restore_ == true 生效*/
	std::string		user_datafile_localbackup_folder_; /**< string 用户数据文件备份（本地）目录，缺省在数据文件所在目录创建一个db_file.back目录 */
	/***********用户数据本地备份与恢复 end************/

	std::string		server_conf_file_path_;			/**< 私有云服务器相关地址配置文件本地绝对路径，如果不填默认执行文件目录下的server_conf.txt */
	
	//private_server_setting 私有服务器配置（设置方法有两种，一个是配置以下信息，一个是通过配置server_conf_file_path_地址，信息从文件中读取）
	bool			use_private_server_;			/**< 是否使用私有服务器，如果使用私有服务器，则必须设置为true */
	std::string		lbs_address_;					/**< lbs地址，如果选择使用私有服务器，则必填 */
	std::string  	nos_lbs_address_;				/**< nos lbs地址，如果选择使用私有服务器，则必填 */
	std::string		default_link_address_;			/**< 默认link服务器地址，如果选择使用私有服务器，则必填 */
	std::string		default_nos_upload_address_;	/**< 默认nos 上传服务器地址，如果选择使用私有服务器，则必填 */
	std::string		default_nos_upload_host_;		/**< 默认nos 上传服务器主机地址，仅 kNIMUseHttps设置为true 时有效，用作 https 上传时的域名校验及 http header host 字段填充 */
	std::string		rsa_public_key_module_;			/**< RSA public key，如果选择使用私有服务器，则必填 */
	int				rsa_version_;					/**< RSA version，如果选择使用私有服务器，则必填 */
	std::string		nos_download_address_;			/**< nos 下载地址拼接模板，用于拼接最终得到的下载地址*/
	std::string		nos_accelerate_host_;			/**< 需要被加速主机名*/
	std::string		nos_accelerate_address_;		/**< nos 加速地址拼接模板，用于获得加速后的下载地址*/
	std::string		ntserver_address_;				/**< 部分 IM 错误信息统计上报地址*/
	bool upload_statistics_data_;					/**< 错误信息统计是否上报*/
	/** 构造函数 */
	SDKConfig();
};

/** @brief 多端登陆客户端信息 */
 struct NIM_SDK_CPPWRAPPER_DLL_API OtherClientPres
{
	std::string	app_account_;			/**< 第三方账号 */
	NIMClientType	client_type_;		/**< 客户端类型, 见NIMClientType */
	std::string	client_os_;				/**< 登录系统类型,比如ios 6.0.1 */
	std::string	mac_address_;			/**< 登录设备的mac地址 */
	std::string	device_id_;				/**< 设备id，uuid */
	int64_t		login_time_;			/**< 本次登陆时间, 精度到ms */
	std::string custom_data_;			/**< 自定义字段/
	/** 构造函数 */
	OtherClientPres() : login_time_(0) {}
};

/** @brief 登录结果回调信息 */
 struct NIM_SDK_CPPWRAPPER_DLL_API LoginRes
{
	NIMResCode res_code_;				/**< 返回的错误码NIMResCode */
	bool relogin_;						/**< 是否为重连过程 */
	NIMLoginStep	login_step_;		/**< 登录步骤NIMLoginStep */
	std::list<OtherClientPres> other_clients_;	/**< 其他端的在线状态列表，登录成功才会返回这部分内容 */
	bool retrying_;						/**< SDK是否在重试，如果为false，开发者需要检查登录步骤和错误码，明确问题后调用手动重连接口进行登录操作 */
	/** 构造函数 */
	LoginRes() : relogin_(false), retrying_(true) {}
};

/** @brief 被踢结果回调信息 */
struct NIM_SDK_CPPWRAPPER_DLL_API KickoutRes
{
	NIMClientType client_type_;			/**< int, 客户端类型NIMClientType */
	NIMKickReason kick_reason_;			/**< 返回的被踢原因NIMKickReason */
};

/** @brief 多端登录回调信息 */
struct NIM_SDK_CPPWRAPPER_DLL_API MultiSpotLoginRes
{
	NIMMultiSpotNotifyType	notify_type_;			/**< NIMMultiSpotNotifyType 多点登录通知类型 */
	std::list<OtherClientPres> other_clients_;		/**< 其他端的在线状态列表 */
};

/** @brief 踢人结果回调信息 */
struct NIM_SDK_CPPWRAPPER_DLL_API KickOtherRes
{
	NIMResCode res_code_;					/**< 返回的错误码NIMResCode */
	std::list<std::string> device_ids_;		/**< 设备id，uuid */
};

/** @fn bool ParseOtherClientsPres(const Json::Value array_objs, std::list<OtherClientPres> &outs)
  * 解析多端登录客户端信息
  * @param[in] array_objs 多端登录客户端信息(Json Value数据)
  * @param[out] outs 多端登录客户端信息
  * @return bool 解析成功 或失败
  */
bool NIM_SDK_CPPWRAPPER_DLL_API ParseOtherClientsPres(const Json::Value array_objs, std::list<OtherClientPres> &outs);

}

#endif //_NIM_SDK_CPP_CLIENT_HELPER_H_