/** ------------------------------------------------------------
 * SPDX-License-Identifier: GPL-3.0-or-later
 * -------------------------------------------------------------
 * File Authors  :  Heng Guo  <2085471348@qq.com>
 * Contributors  : Aoran Zeng <ccmywish@qq.com>
 *               | Yangmoooo <yangmoooo@outlook.com>
 *               | happy game <happygame1024@gmail.com>
 *               |
 * Created On    : <2023-09-06>
 * Last Modified : <2025-07-21>
 * ------------------------------------------------------------*/

static SourceProvider_t os_openEuler_upstream =
{
  def_upstream, "https://repo.openeuler.org/",
  {NotSkip, NA, NA, "https://repo.openeuler.org/openEuler-24.03-LTS/ISO/x86_64/openEuler-24.03-LTS-netinst-x86_64-dvd.iso", ACCURATE} // 896MB
};


/**
 * @update 2025-06-20
 */
static Source_t os_openeuler_sources[] =
{
  {&os_openEuler_upstream, "https://repo.openeuler.org/",         DelegateToUpstream},
  {&Ali,              "https://mirrors.aliyun.com/openeuler/",     DelegateToMirror},
  {&Bfsu,             "https://mirrors.bfsu.edu.cn/openeuler/",    DelegateToMirror},
  {&Ustc,             "https://mirrors.ustc.edu.cn/openeuler/",    DelegateToMirror},
  {&Tuna,             "https://mirrors.tuna.tsinghua.edu.cn/openeuler/", DelegateToMirror},
  {&Tencent,          "https://mirrors.tencent.com/openeuler/",    DelegateToMirror},
  // {&Tencent_Intra, "https://mirrors.tencentyun.com/openeuler/", DelegateToMirror},

  /* 不启用原因：过慢 */
  // {&Netease,          "https://mirrors.163.com/openeuler/",  DelegateToMirror}
  /* 不启用原因：过慢 */
  // {&Sohu,             "https://mirrors.sohu.com/openeuler/", DelegateToMirror}
};
def_sources_n(os_openeuler);


/**
 * chsrc get openeuler
 */
void
os_openeuler_getsrc (char *option)
{
  chsrc_view_file (OS_openEuler_SourceList);
}


/**
 * chsrc set openeuler
 */
void
os_openeuler_setsrc (char *option)
{
  chsrc_ensure_root ();

  chsrc_yield_source_and_confirm (os_openeuler);

  chsrc_backup (OS_openEuler_SourceList);

  // 替换 baseurl=<<URL>>/openEuler-xx.xx/...
  // openEuler-xx.xx 为 openEuler 版本号
  // sed -E 's!^baseurl=.*?/openEuler-([^/]+)!baseurl=$(source.url)/openEuler-\1/!g' OS_openEuler_SourceList
  char* cmd = xy_strjoin (6, "sed ",
         "-i -E 's!^baseurl=.*?/openEuler-([^/]+)!baseurl=",
         source.url,
         "openEuler-\\1",
         "!g' ",
         OS_openEuler_SourceList);
  chsrc_run (cmd, RunOpt_Default);

  chsrc_run ("dnf makecache", RunOpt_No_Last_New_Line);

  chsrc_determine_chgtype (ChgType_Auto);
  chsrc_conclude (&source);
}


/**
 * chsrc reset openeuler
 */
void
os_openeuler_resetsrc (char *option)
{
  os_openeuler_setsrc (option);
}


/**
 * chsrc ls openeuler
 */
Feature_t
os_openeuler_feat (char *option)
{
  Feature_t f = {0};

  f.can_get = true;
  f.can_reset = true;

  f.cap_locally = CanNot;
  f.cap_locally_explain = NULL;
  f.can_english = true;
  f.can_user_define = true;

  f.note = NULL;

  return f;
}

def_target_gsrf(os_openeuler);
