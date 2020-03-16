#include "c/schemas/ModioComment.h"
#include <string.h>                 // for strcpy, NULL
#include <string>                   // for string
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioComment
#include "c/schemas/ModioUser.h"    // for modioInitUser

extern "C"
{
  void modioInitComment(ModioComment *comment, nlohmann::json comment_json)
  {
    comment->id = 0;
    if (modio::hasKey(comment_json, "id"))
      comment->id = comment_json["id"];

    comment->mod_id = 0;
    if (modio::hasKey(comment_json, "mod_id"))
      comment->mod_id = comment_json["mod_id"];

    comment->date_added = 0;
    if (modio::hasKey(comment_json, "date_added"))
      comment->date_added = comment_json["date_added"];

    comment->reply_id = 0;
    if (modio::hasKey(comment_json, "reply_id"))
      comment->reply_id = comment_json["reply_id"];

    comment->karma = 0;
    if (modio::hasKey(comment_json, "karma"))
      comment->karma = comment_json["karma"];

    comment->karma_guest = 0;
    if (modio::hasKey(comment_json, "karma_guest"))
      comment->karma_guest = comment_json["karma_guest"];

    comment->thread_position = NULL;
    if (modio::hasKey(comment_json, "thread_position"))
    {
      std::string thread_position_str = comment_json["thread_position"];
      comment->thread_position = new char[thread_position_str.size() + 1];
      strcpy(comment->thread_position, thread_position_str.c_str());
    }

    comment->content = NULL;
    if (modio::hasKey(comment_json, "content"))
    {
      std::string content_str = comment_json["content"];
      comment->content = new char[content_str.size() + 1];
      strcpy(comment->content, content_str.c_str());
    }

    nlohmann::json user_json;
    if (modio::hasKey(comment_json, "user"))
      user_json = comment_json["user"];
    modioInitUser(&(comment->user), user_json);
  }

  void modioInitCommentCpp(ModioComment* modio_comment, modio::Comment* comment)
  {
    modio_comment->id = comment->id;
    modio_comment->mod_id = comment->mod_id;
    modio_comment->date_added = comment->date_added;
    modio_comment->reply_id = comment->reply_id;
    modio_comment->karma = comment->karma;
    modio_comment->karma_guest = comment->karma_guest;

    modio_comment->thread_position = new char[comment->thread_position.size() + 1];
    strcpy(modio_comment->thread_position, comment->thread_position.c_str());

    modio_comment->content = new char[comment->content.size() + 1];
    strcpy(modio_comment->content, comment->content.c_str());
  }

  void modioFreeComment(ModioComment *comment)
  {
    if (comment)
    {
      if (comment->thread_position)
        delete[] comment->thread_position;
      if (comment->content)
        delete[] comment->content;
      modioFreeUser(&(comment->user));
    }
  }
}
