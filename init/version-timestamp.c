// SPDX-License-Identifier: GPL-2.0-only

#include <generated/compile.h>
#include <generated/utsrelease.h>
#include <linux/proc_ns.h>
#include <linux/refcount.h>
#include <linux/uts.h>
#include <linux/utsname.h>

#ifdef CONFIG_REPORTED_UTS
static_assert(sizeof(CONFIG_REPORTED_UTS_RELEASE) > 1);
static_assert(sizeof(CONFIG_REPORTED_UTS_VERSION) > 1);
static_assert(sizeof(CONFIG_REPORTED_UTS_RELEASE) <= __NEW_UTS_LEN + 1);
static_assert(sizeof("#" CONFIG_REPORTED_UTS_VERSION) <= __NEW_UTS_LEN + 1);
#endif

struct uts_namespace init_uts_ns = {
	.ns.count = REFCOUNT_INIT(2),
	.name = {
		.sysname	= UTS_SYSNAME,
		.nodename	= UTS_NODENAME,
#ifdef CONFIG_REPORTED_UTS
		.release	= CONFIG_REPORTED_UTS_RELEASE,
		.version	= "#" CONFIG_REPORTED_UTS_VERSION,
#else
		.release	= UTS_RELEASE,
		.version	= UTS_VERSION,
#endif
		.machine	= UTS_MACHINE,
		.domainname	= UTS_DOMAINNAME,
	},
	.user_ns = &init_user_ns,
	.ns.inum = PROC_UTS_INIT_INO,
#ifdef CONFIG_UTS_NS
	.ns.ops = &utsns_operations,
#endif
};

/* FIXED STRINGS! Don't touch! */
const char linux_banner[] =
	"Linux version " UTS_RELEASE " (" LINUX_COMPILE_BY "@"
	LINUX_COMPILE_HOST ") (" LINUX_COMPILER ") " UTS_VERSION "\n";
