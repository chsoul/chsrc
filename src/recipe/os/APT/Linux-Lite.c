/** ------------------------------------------------------------
 * SPDX-License-Identifier: GPL-3.0-or-later
 * -------------------------------------------------------------
 * File Authors  : Aoran Zeng <ccmywish@qq.com>
 * Contributors  : Yangmoooo <yangmoooo@outlook.com>
 *               |
 * Created On    : <2023-09-29>
 * Last Modified : <2024-12-18>
 * ------------------------------------------------------------*/

static SourceProvider_t os_linuxlite_upstream =
{
  def_upstream, "http://repo.linuxliteos.com/linuxlite/",
  {NotSkip, NA, NA, "http://repo.linuxliteos.com/linuxlite/isos/7.2/linux-lite-7.2-64bit.iso", ACCURATE} // 2.9GB
};

/**
 * @update 2024-11-21
 */
static Source_t os_linuxlite_sources[] =
{
  {&os_linuxlite_upstream, "http://repo.linuxliteos.com/linuxlite/"},
  {&MirrorZ,          "https://mirrors.cernet.edu.cn/linuxliteos/"},
  {&Sjtug_Zhiyuan,    "https://mirrors.sjtug.sjtu.edu.cn/linuxliteos/"},
  {&Nju,              "https://mirror.nju.edu.cn/linuxliteos/"}
};
def_sources_n(os_linuxlite);


void
os_linuxlite_getsrc (char *option)
{
  chsrc_view_file (OS_Apt_SourceList);
}

/**
 * @consult https://help.mirrors.cernet.edu.cn/linuxliteos/
 */
void
os_linuxlite_setsrc (char *option)
{
  chsrc_ensure_root ();

  chsrc_yield_source_and_confirm (os_linuxlite);

  chsrc_backup (OS_Apt_SourceList);

  char *cmd = xy_strjoin (3, "sed -E -i 's@https?://.*/.*/?@", source.url, "@g' " OS_Apt_SourceList);

  chsrc_run ("apt update", RunOpt_No_Last_New_Line);

  chsrc_determine_chgtype (ChgType_Auto);
  chsrc_conclude (&source);
}

def_target(os_linuxlite);
