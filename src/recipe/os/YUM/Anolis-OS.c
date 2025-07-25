/** ------------------------------------------------------------
 * SPDX-License-Identifier: GPL-3.0-or-later
 * -------------------------------------------------------------
 * File Authors  : Aoran Zeng <ccmywish@qq.com>
 * Contributors  :  Nil Null  <nil@null.org>
 * Created On    : <2023-09-24>
 * Last Modified : <2024-08-16>
 *
 * Anolis OS 为这个操作系统的名字，OpenAnolis(龙蜥社区) 只是社区名
 * ------------------------------------------------------------*/

/**
 * @update 2024-06-12
 */
static Source_t os_anolis_sources[] =
{
  {&UpstreamProvider,  NULL, NULL},
  {&Ali,              "https://mirrors.aliyun.com/anolis",  DelegateToMirror},
  {&Hust,             "https://mirrors.hust.edu.cn/anolis", DelegateToMirror}
};
def_sources_n(os_anolis);


/**
 * @consult: https://mirrors.hust.edu.cn/docs/anolis
 */
void
os_anolis_setsrc (char *option)
{
  chsrc_ensure_root ();

  chsrc_yield_source_and_confirm (os_anolis);

  char *cmd = xy_strjoin (3, "sed -i.bak -E 's|https?://(mirrors\\.openanolis\\.cn/anolis)|", source.url, "|g' /etc/yum.repos.d/*.repo");
  chsrc_run (cmd, RunOpt_Default);

  chsrc_run ("dnf makecache", RunOpt_Default);
  chsrc_run ("dnf update", RunOpt_No_Last_New_Line);

  chsrc_determine_chgtype (ChgType_Untested);
  chsrc_conclude (&source);
}


Feature_t
os_anolis_feat (char *option)
{
  Feature_t f = {0};

  f.can_get = false;
  f.can_reset = false;

  f.cap_locally = CanNot;
  f.cap_locally_explain = NULL;
  f.can_english = true;
  f.can_user_define = false;

  f.note = NULL;
  return f;
}

def_target_sf(os_anolis);
