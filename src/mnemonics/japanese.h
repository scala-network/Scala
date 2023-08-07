// Word list originally created by dabura667 and released under The MIT License
// (MIT)
//
// The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// Code surrounding the word list is Copyright (c) 2014-2023, The scala Project
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list
//    of conditions and the following disclaimer in the documentation and/or
//    other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be
//    used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

/*!
 * \file japanese.h
 *
 * \brief Japanese word list and map.
 */

#ifndef JAPANESE_H
#define JAPANESE_H

#include <vector>
#include <unordered_map>
#include "language_base.h"
#include <string>

/*!
 * \namespace Language
 * \brief Mnemonic language related namespace.
 */
namespace Language {
class Japanese : public Base {
public:
  Japanese() : Base("日本語", "Japanese", {}, 3) {
    static constexpr const char *const words[NWORDS] = {
        "あいこくしん",   "あいさつ",     "あいだ",         "あおぞら",
        "あかちゃん",     "あきる",       "あけがた",       "あける",
        "あこがれる",     "あさい",       "あさひ",         "あしあと",
        "あじわう",       "あずかる",     "あずき",         "あそぶ",
        "あたえる",       "あたためる",   "あたりまえ",     "あたる",
        "あつい",         "あつかう",     "あっしゅく",     "あつまり",
        "あつめる",       "あてな",       "あてはまる",     "あひる",
        "あぶら",         "あぶる",       "あふれる",       "あまい",
        "あまど",         "あまやかす",   "あまり",         "あみもの",
        "あめりか",       "あやまる",     "あゆむ",         "あらいぐま",
        "あらし",         "あらすじ",     "あらためる",     "あらゆる",
        "あらわす",       "ありがとう",   "あわせる",       "あわてる",
        "あんい",         "あんがい",     "あんこ",         "あんぜん",
        "あんてい",       "あんない",     "あんまり",       "いいだす",
        "いおん",         "いがい",       "いがく",         "いきおい",
        "いきなり",       "いきもの",     "いきる",         "いくじ",
        "いくぶん",       "いけばな",     "いけん",         "いこう",
        "いこく",         "いこつ",       "いさましい",     "いさん",
        "いしき",         "いじゅう",     "いじょう",       "いじわる",
        "いずみ",         "いずれ",       "いせい",         "いせえび",
        "いせかい",       "いせき",       "いぜん",         "いそうろう",
        "いそがしい",     "いだい",       "いだく",         "いたずら",
        "いたみ",         "いたりあ",     "いちおう",       "いちじ",
        "いちど",         "いちば",       "いちぶ",         "いちりゅう",
        "いつか",         "いっしゅん",   "いっせい",       "いっそう",
        "いったん",       "いっち",       "いってい",       "いっぽう",
        "いてざ",         "いてん",       "いどう",         "いとこ",
        "いない",         "いなか",       "いねむり",       "いのち",
        "いのる",         "いはつ",       "いばる",         "いはん",
        "いびき",         "いひん",       "いふく",         "いへん",
        "いほう",         "いみん",       "いもうと",       "いもたれ",
        "いもり",         "いやがる",     "いやす",         "いよかん",
        "いよく",         "いらい",       "いらすと",       "いりぐち",
        "いりょう",       "いれい",       "いれもの",       "いれる",
        "いろえんぴつ",   "いわい",       "いわう",         "いわかん",
        "いわば",         "いわゆる",     "いんげんまめ",   "いんさつ",
        "いんしょう",     "いんよう",     "うえき",         "うえる",
        "うおざ",         "うがい",       "うかぶ",         "うかべる",
        "うきわ",         "うくらいな",   "うくれれ",       "うけたまわる",
        "うけつけ",       "うけとる",     "うけもつ",       "うける",
        "うごかす",       "うごく",       "うこん",         "うさぎ",
        "うしなう",       "うしろがみ",   "うすい",         "うすぎ",
        "うすぐらい",     "うすめる",     "うせつ",         "うちあわせ",
        "うちがわ",       "うちき",       "うちゅう",       "うっかり",
        "うつくしい",     "うったえる",   "うつる",         "うどん",
        "うなぎ",         "うなじ",       "うなずく",       "うなる",
        "うねる",         "うのう",       "うぶげ",         "うぶごえ",
        "うまれる",       "うめる",       "うもう",         "うやまう",
        "うよく",         "うらがえす",   "うらぐち",       "うらない",
        "うりあげ",       "うりきれ",     "うるさい",       "うれしい",
        "うれゆき",       "うれる",       "うろこ",         "うわき",
        "うわさ",         "うんこう",     "うんちん",       "うんてん",
        "うんどう",       "えいえん",     "えいが",         "えいきょう",
        "えいご",         "えいせい",     "えいぶん",       "えいよう",
        "えいわ",         "えおり",       "えがお",         "えがく",
        "えきたい",       "えくせる",     "えしゃく",       "えすて",
        "えつらん",       "えのぐ",       "えほうまき",     "えほん",
        "えまき",         "えもじ",       "えもの",         "えらい",
        "えらぶ",         "えりあ",       "えんえん",       "えんかい",
        "えんぎ",         "えんげき",     "えんしゅう",     "えんぜつ",
        "えんそく",       "えんちょう",   "えんとつ",       "おいかける",
        "おいこす",       "おいしい",     "おいつく",       "おうえん",
        "おうさま",       "おうじ",       "おうせつ",       "おうたい",
        "おうふく",       "おうべい",     "おうよう",       "おえる",
        "おおい",         "おおう",       "おおどおり",     "おおや",
        "おおよそ",       "おかえり",     "おかず",         "おがむ",
        "おかわり",       "おぎなう",     "おきる",         "おくさま",
        "おくじょう",     "おくりがな",   "おくる",         "おくれる",
        "おこす",         "おこなう",     "おこる",         "おさえる",
        "おさない",       "おさめる",     "おしいれ",       "おしえる",
        "おじぎ",         "おじさん",     "おしゃれ",       "おそらく",
        "おそわる",       "おたがい",     "おたく",         "おだやか",
        "おちつく",       "おっと",       "おつり",         "おでかけ",
        "おとしもの",     "おとなしい",   "おどり",         "おどろかす",
        "おばさん",       "おまいり",     "おめでとう",     "おもいで",
        "おもう",         "おもたい",     "おもちゃ",       "おやつ",
        "おやゆび",       "およぼす",     "おらんだ",       "おろす",
        "おんがく",       "おんけい",     "おんしゃ",       "おんせん",
        "おんだん",       "おんちゅう",   "おんどけい",     "かあつ",
        "かいが",         "がいき",       "がいけん",       "がいこう",
        "かいさつ",       "かいしゃ",     "かいすいよく",   "かいぜん",
        "かいぞうど",     "かいつう",     "かいてん",       "かいとう",
        "かいふく",       "がいへき",     "かいほう",       "かいよう",
        "がいらい",       "かいわ",       "かえる",         "かおり",
        "かかえる",       "かがく",       "かがし",         "かがみ",
        "かくご",         "かくとく",     "かざる",         "がぞう",
        "かたい",         "かたち",       "がちょう",       "がっきゅう",
        "がっこう",       "がっさん",     "がっしょう",     "かなざわし",
        "かのう",         "がはく",       "かぶか",         "かほう",
        "かほご",         "かまう",       "かまぼこ",       "かめれおん",
        "かゆい",         "かようび",     "からい",         "かるい",
        "かろう",         "かわく",       "かわら",         "がんか",
        "かんけい",       "かんこう",     "かんしゃ",       "かんそう",
        "かんたん",       "かんち",       "がんばる",       "きあい",
        "きあつ",         "きいろ",       "ぎいん",         "きうい",
        "きうん",         "きえる",       "きおう",         "きおく",
        "きおち",         "きおん",       "きかい",         "きかく",
        "きかんしゃ",     "ききて",       "きくばり",       "きくらげ",
        "きけんせい",     "きこう",       "きこえる",       "きこく",
        "きさい",         "きさく",       "きさま",         "きさらぎ",
        "ぎじかがく",     "ぎしき",       "ぎじたいけん",   "ぎじにってい",
        "ぎじゅつしゃ",   "きすう",       "きせい",         "きせき",
        "きせつ",         "きそう",       "きぞく",         "きぞん",
        "きたえる",       "きちょう",     "きつえん",       "ぎっちり",
        "きつつき",       "きつね",       "きてい",         "きどう",
        "きどく",         "きない",       "きなが",         "きなこ",
        "きぬごし",       "きねん",       "きのう",         "きのした",
        "きはく",         "きびしい",     "きひん",         "きふく",
        "きぶん",         "きぼう",       "きほん",         "きまる",
        "きみつ",         "きむずかしい", "きめる",         "きもだめし",
        "きもち",         "きもの",       "きゃく",         "きやく",
        "ぎゅうにく",     "きよう",       "きょうりゅう",   "きらい",
        "きらく",         "きりん",       "きれい",         "きれつ",
        "きろく",         "ぎろん",       "きわめる",       "ぎんいろ",
        "きんかくじ",     "きんじょ",     "きんようび",     "ぐあい",
        "くいず",         "くうかん",     "くうき",         "くうぐん",
        "くうこう",       "ぐうせい",     "くうそう",       "ぐうたら",
        "くうふく",       "くうぼ",       "くかん",         "くきょう",
        "くげん",         "ぐこう",       "くさい",         "くさき",
        "くさばな",       "くさる",       "くしゃみ",       "くしょう",
        "くすのき",       "くすりゆび",   "くせげ",         "くせん",
        "ぐたいてき",     "くださる",     "くたびれる",     "くちこみ",
        "くちさき",       "くつした",     "ぐっすり",       "くつろぐ",
        "くとうてん",     "くどく",       "くなん",         "くねくね",
        "くのう",         "くふう",       "くみあわせ",     "くみたてる",
        "くめる",         "くやくしょ",   "くらす",         "くらべる",
        "くるま",         "くれる",       "くろう",         "くわしい",
        "ぐんかん",       "ぐんしょく",   "ぐんたい",       "ぐんて",
        "けあな",         "けいかく",     "けいけん",       "けいこ",
        "けいさつ",       "げいじゅつ",   "けいたい",       "げいのうじん",
        "けいれき",       "けいろ",       "けおとす",       "けおりもの",
        "げきか",         "げきげん",     "げきだん",       "げきちん",
        "げきとつ",       "げきは",       "げきやく",       "げこう",
        "げこくじょう",   "げざい",       "けさき",         "げざん",
        "けしき",         "けしごむ",     "けしょう",       "げすと",
        "けたば",         "けちゃっぷ",   "けちらす",       "けつあつ",
        "けつい",         "けつえき",     "けっこん",       "けつじょ",
        "けっせき",       "けってい",     "けつまつ",       "げつようび",
        "げつれい",       "けつろん",     "げどく",         "けとばす",
        "けとる",         "けなげ",       "けなす",         "けなみ",
        "けぬき",         "げねつ",       "けねん",         "けはい",
        "げひん",         "けぶかい",     "げぼく",         "けまり",
        "けみかる",       "けむし",       "けむり",         "けもの",
        "けらい",         "けろけろ",     "けわしい",       "けんい",
        "けんえつ",       "けんお",       "けんか",         "げんき",
        "けんげん",       "けんこう",     "けんさく",       "けんしゅう",
        "けんすう",       "げんそう",     "けんちく",       "けんてい",
        "けんとう",       "けんない",     "けんにん",       "げんぶつ",
        "けんま",         "けんみん",     "けんめい",       "けんらん",
        "けんり",         "こあくま",     "こいぬ",         "こいびと",
        "ごうい",         "こうえん",     "こうおん",       "こうかん",
        "ごうきゅう",     "ごうけい",     "こうこう",       "こうさい",
        "こうじ",         "こうすい",     "ごうせい",       "こうそく",
        "こうたい",       "こうちゃ",     "こうつう",       "こうてい",
        "こうどう",       "こうない",     "こうはい",       "ごうほう",
        "ごうまん",       "こうもく",     "こうりつ",       "こえる",
        "こおり",         "ごかい",       "ごがつ",         "ごかん",
        "こくご",         "こくさい",     "こくとう",       "こくない",
        "こくはく",       "こぐま",       "こけい",         "こける",
        "ここのか",       "こころ",       "こさめ",         "こしつ",
        "こすう",         "こせい",       "こせき",         "こぜん",
        "こそだて",       "こたい",       "こたえる",       "こたつ",
        "こちょう",       "こっか",       "こつこつ",       "こつばん",
        "こつぶ",         "こてい",       "こてん",         "ことがら",
        "ことし",         "ことば",       "ことり",         "こなごな",
        "こねこね",       "このまま",     "このみ",         "このよ",
        "ごはん",         "こひつじ",     "こふう",         "こふん",
        "こぼれる",       "ごまあぶら",   "こまかい",       "ごますり",
        "こまつな",       "こまる",       "こむぎこ",       "こもじ",
        "こもち",         "こもの",       "こもん",         "こやく",
        "こやま",         "こゆう",       "こゆび",         "こよい",
        "こよう",         "こりる",       "これくしょん",   "ころっけ",
        "こわもて",       "こわれる",     "こんいん",       "こんかい",
        "こんき",         "こんしゅう",   "こんすい",       "こんだて",
        "こんとん",       "こんなん",     "こんびに",       "こんぽん",
        "こんまけ",       "こんや",       "こんれい",       "こんわく",
        "ざいえき",       "さいかい",     "さいきん",       "ざいげん",
        "ざいこ",         "さいしょ",     "さいせい",       "ざいたく",
        "ざいちゅう",     "さいてき",     "ざいりょう",     "さうな",
        "さかいし",       "さがす",       "さかな",         "さかみち",
        "さがる",         "さぎょう",     "さくし",         "さくひん",
        "さくら",         "さこく",       "さこつ",         "さずかる",
        "ざせき",         "さたん",       "さつえい",       "ざつおん",
        "ざっか",         "ざつがく",     "さっきょく",     "ざっし",
        "さつじん",       "ざっそう",     "さつたば",       "さつまいも",
        "さてい",         "さといも",     "さとう",         "さとおや",
        "さとし",         "さとる",       "さのう",         "さばく",
        "さびしい",       "さべつ",       "さほう",         "さほど",
        "さます",         "さみしい",     "さみだれ",       "さむけ",
        "さめる",         "さやえんどう", "さゆう",         "さよう",
        "さよく",         "さらだ",       "ざるそば",       "さわやか",
        "さわる",         "さんいん",     "さんか",         "さんきゃく",
        "さんこう",       "さんさい",     "ざんしょ",       "さんすう",
        "さんせい",       "さんそ",       "さんち",         "さんま",
        "さんみ",         "さんらん",     "しあい",         "しあげ",
        "しあさって",     "しあわせ",     "しいく",         "しいん",
        "しうち",         "しえい",       "しおけ",         "しかい",
        "しかく",         "じかん",       "しごと",         "しすう",
        "じだい",         "したうけ",     "したぎ",         "したて",
        "したみ",         "しちょう",     "しちりん",       "しっかり",
        "しつじ",         "しつもん",     "してい",         "してき",
        "してつ",         "じてん",       "じどう",         "しなぎれ",
        "しなもの",       "しなん",       "しねま",         "しねん",
        "しのぐ",         "しのぶ",       "しはい",         "しばかり",
        "しはつ",         "しはらい",     "しはん",         "しひょう",
        "しふく",         "じぶん",       "しへい",         "しほう",
        "しほん",         "しまう",       "しまる",         "しみん",
        "しむける",       "じむしょ",     "しめい",         "しめる",
        "しもん",         "しゃいん",     "しゃうん",       "しゃおん",
        "じゃがいも",     "しやくしょ",   "しゃくほう",     "しゃけん",
        "しゃこ",         "しゃざい",     "しゃしん",       "しゃせん",
        "しゃそう",       "しゃたい",     "しゃちょう",     "しゃっきん",
        "じゃま",         "しゃりん",     "しゃれい",       "じゆう",
        "じゅうしょ",     "しゅくはく",   "じゅしん",       "しゅっせき",
        "しゅみ",         "しゅらば",     "じゅんばん",     "しょうかい",
        "しょくたく",     "しょっけん",   "しょどう",       "しょもつ",
        "しらせる",       "しらべる",     "しんか",         "しんこう",
        "じんじゃ",       "しんせいじ",   "しんちく",       "しんりん",
        "すあげ",         "すあし",       "すあな",         "ずあん",
        "すいえい",       "すいか",       "すいとう",       "ずいぶん",
        "すいようび",     "すうがく",     "すうじつ",       "すうせん",
        "すおどり",       "すきま",       "すくう",         "すくない",
        "すける",         "すごい",       "すこし",         "ずさん",
        "すずしい",       "すすむ",       "すすめる",       "すっかり",
        "ずっしり",       "ずっと",       "すてき",         "すてる",
        "すねる",         "すのこ",       "すはだ",         "すばらしい",
        "ずひょう",       "ずぶぬれ",     "すぶり",         "すふれ",
        "すべて",         "すべる",       "ずほう",         "すぼん",
        "すまい",         "すめし",       "すもう",         "すやき",
        "すらすら",       "するめ",       "すれちがう",     "すろっと",
        "すわる",         "すんぜん",     "すんぽう",       "せあぶら",
        "せいかつ",       "せいげん",     "せいじ",         "せいよう",
        "せおう",         "せかいかん",   "せきにん",       "せきむ",
        "せきゆ",         "せきらんうん", "せけん",         "せこう",
        "せすじ",         "せたい",       "せたけ",         "せっかく",
        "せっきゃく",     "ぜっく",       "せっけん",       "せっこつ",
        "せっさたくま",   "せつぞく",     "せつだん",       "せつでん",
        "せっぱん",       "せつび",       "せつぶん",       "せつめい",
        "せつりつ",       "せなか",       "せのび",         "せはば",
        "せびろ",         "せぼね",       "せまい",         "せまる",
        "せめる",         "せもたれ",     "せりふ",         "ぜんあく",
        "せんい",         "せんえい",     "せんか",         "せんきょ",
        "せんく",         "せんげん",     "ぜんご",         "せんさい",
        "せんしゅ",       "せんすい",     "せんせい",       "せんぞ",
        "せんたく",       "せんちょう",   "せんてい",       "せんとう",
        "せんぬき",       "せんねん",     "せんぱい",       "ぜんぶ",
        "ぜんぽう",       "せんむ",       "せんめんじょ",   "せんもん",
        "せんやく",       "せんゆう",     "せんよう",       "ぜんら",
        "ぜんりゃく",     "せんれい",     "せんろ",         "そあく",
        "そいとげる",     "そいね",       "そうがんきょう", "そうき",
        "そうご",         "そうしん",     "そうだん",       "そうなん",
        "そうび",         "そうめん",     "そうり",         "そえもの",
        "そえん",         "そがい",       "そげき",         "そこう",
        "そこそこ",       "そざい",       "そしな",         "そせい",
        "そせん",         "そそぐ",       "そだてる",       "そつう",
        "そつえん",       "そっかん",     "そつぎょう",     "そっけつ",
        "そっこう",       "そっせん",     "そっと",         "そとがわ",
        "そとづら",       "そなえる",     "そなた",         "そふぼ",
        "そぼく",         "そぼろ",       "そまつ",         "そまる",
        "そむく",         "そむりえ",     "そめる",         "そもそも",
        "そよかぜ",       "そらまめ",     "そろう",         "そんかい",
        "そんけい",       "そんざい",     "そんしつ",       "そんぞく",
        "そんちょう",     "ぞんび",       "ぞんぶん",       "そんみん",
        "たあい",         "たいいん",     "たいうん",       "たいえき",
        "たいおう",       "だいがく",     "たいき",         "たいぐう",
        "たいけん",       "たいこ",       "たいざい",       "だいじょうぶ",
        "だいすき",       "たいせつ",     "たいそう",       "だいたい",
        "たいちょう",     "たいてい",     "だいどころ",     "たいない",
        "たいねつ",       "たいのう",     "たいはん",       "だいひょう",
        "たいふう",       "たいへん",     "たいほ",         "たいまつばな",
        "たいみんぐ",     "たいむ",       "たいめん",       "たいやき",
        "たいよう",       "たいら",       "たいりょく",     "たいる",
        "たいわん",       "たうえ",       "たえる",         "たおす",
        "たおる",         "たおれる",     "たかい",         "たかね",
        "たきび",         "たくさん",     "たこく",         "たこやき",
        "たさい",         "たしざん",     "だじゃれ",       "たすける",
        "たずさわる",     "たそがれ",     "たたかう",       "たたく",
        "ただしい",       "たたみ",       "たちばな",       "だっかい",
        "だっきゃく",     "だっこ",       "だっしゅつ",     "だったい",
        "たてる",         "たとえる",     "たなばた",       "たにん",
        "たぬき",         "たのしみ",     "たはつ",         "たぶん",
        "たべる",         "たぼう",       "たまご",         "たまる",
        "だむる",         "ためいき",     "ためす",         "ためる",
        "たもつ",         "たやすい",     "たよる",         "たらす",
        "たりきほんがん", "たりょう",     "たりる",         "たると",
        "たれる",         "たれんと",     "たろっと",       "たわむれる",
        "だんあつ",       "たんい",       "たんおん",       "たんか",
        "たんき",         "たんけん",     "たんご",         "たんさん",
        "たんじょうび",   "だんせい",     "たんそく",       "たんたい",
        "だんち",         "たんてい",     "たんとう",       "だんな",
        "たんにん",       "だんねつ",     "たんのう",       "たんぴん",
        "だんぼう",       "たんまつ",     "たんめい",       "だんれつ",
        "だんろ",         "だんわ",       "ちあい",         "ちあん",
        "ちいき",         "ちいさい",     "ちえん",         "ちかい",
        "ちから",         "ちきゅう",     "ちきん",         "ちけいず",
        "ちけん",         "ちこく",       "ちさい",         "ちしき",
        "ちしりょう",     "ちせい",       "ちそう",         "ちたい",
        "ちたん",         "ちちおや",     "ちつじょ",       "ちてき",
        "ちてん",         "ちぬき",       "ちぬり",         "ちのう",
        "ちひょう",       "ちへいせん",   "ちほう",         "ちまた",
        "ちみつ",         "ちみどろ",     "ちめいど",       "ちゃんこなべ",
        "ちゅうい",       "ちゆりょく",   "ちょうし",       "ちょさくけん",
        "ちらし",         "ちらみ",       "ちりがみ",       "ちりょう",
        "ちるど",         "ちわわ",       "ちんたい",       "ちんもく",
        "ついか",         "ついたち",     "つうか",         "つうじょう",
        "つうはん",       "つうわ",       "つかう",         "つかれる",
        "つくね",         "つくる",       "つけね",         "つける",
        "つごう",         "つたえる",     "つづく",         "つつじ",
        "つつむ",         "つとめる",     "つながる",       "つなみ",
        "つねづね",       "つのる",       "つぶす",         "つまらない",
        "つまる",         "つみき",       "つめたい",       "つもり",
        "つもる",         "つよい",       "つるぼ",         "つるみく",
        "つわもの",       "つわり",       "てあし",         "てあて",
        "てあみ",         "ていおん",     "ていか",         "ていき",
        "ていけい",       "ていこく",     "ていさつ",       "ていし",
        "ていせい",       "ていたい",     "ていど",         "ていねい",
        "ていひょう",     "ていへん",     "ていぼう",       "てうち",
        "ておくれ",       "てきとう",     "てくび",         "でこぼこ",
        "てさぎょう",     "てさげ",       "てすり",         "てそう",
        "てちがい",       "てちょう",     "てつがく",       "てつづき",
        "でっぱ",         "てつぼう",     "てつや",         "でぬかえ",
        "てぬき",         "てぬぐい",     "てのひら",       "てはい",
        "てぶくろ",       "てふだ",       "てほどき",       "てほん",
        "てまえ",         "てまきずし",   "てみじか",       "てみやげ",
        "てらす",         "てれび",       "てわけ",         "てわたし",
        "でんあつ",       "てんいん",     "てんかい",       "てんき",
        "てんぐ",         "てんけん",     "てんごく",       "てんさい",
        "てんし",         "てんすう",     "でんち",         "てんてき",
        "てんとう",       "てんない",     "てんぷら",       "てんぼうだい",
        "てんめつ",       "てんらんかい", "でんりょく",     "でんわ",
        "どあい",         "といれ",       "どうかん",       "とうきゅう",
        "どうぐ",         "とうし",       "とうむぎ",       "とおい",
        "とおか",         "とおく",       "とおす",         "とおる",
        "とかい",         "とかす",       "ときおり",       "ときどき",
        "とくい",         "とくしゅう",   "とくてん",       "とくに",
        "とくべつ",       "とけい",       "とける",         "とこや",
        "とさか",         "としょかん",   "とそう",         "とたん",
        "とちゅう",       "とっきゅう",   "とっくん",       "とつぜん",
        "とつにゅう",     "とどける",     "ととのえる",     "とない",
        "となえる",       "となり",       "とのさま",       "とばす",
        "どぶがわ",       "とほう",       "とまる",         "とめる",
        "ともだち",       "ともる",       "どようび",       "とらえる",
        "とんかつ",       "どんぶり",     "ないかく",       "ないこう",
        "ないしょ",       "ないす",       "ないせん",       "ないそう",
        "なおす",         "ながい",       "なくす",         "なげる",
        "なこうど",       "なさけ",       "なたでここ",     "なっとう",
        "なつやすみ",     "ななおし",     "なにごと",       "なにもの",
        "なにわ",         "なのか",       "なふだ",         "なまいき",
        "なまえ",         "なまみ",       "なみだ",         "なめらか",
        "なめる",         "なやむ",       "ならう",         "ならび",
        "ならぶ",         "なれる",       "なわとび",       "なわばり",
        "にあう",         "にいがた",     "にうけ",         "におい",
        "にかい",         "にがて",       "にきび",         "にくしみ",
        "にくまん",       "にげる",       "にさんかたんそ", "にしき",
        "にせもの",       "にちじょう",   "にちようび",     "にっか",
        "にっき",         "にっけい",     "にっこう",       "にっさん",
        "にっしょく",     "にっすう",     "にっせき",       "にってい",
        "になう",         "にほん",       "にまめ",         "にもつ",
        "にやり",         "にゅういん",   "にりんしゃ",     "にわとり",
        "にんい",         "にんか",       "にんき",         "にんげん",
        "にんしき",       "にんずう",     "にんそう",       "にんたい",
        "にんち",         "にんてい",     "にんにく",       "にんぷ",
        "にんまり",       "にんむ",       "にんめい",       "にんよう",
        "ぬいくぎ",       "ぬかす",       "ぬぐいとる",     "ぬぐう",
        "ぬくもり",       "ぬすむ",       "ぬまえび",       "ぬめり",
        "ぬらす",         "ぬんちゃく",   "ねあげ",         "ねいき",
        "ねいる",         "ねいろ",       "ねぐせ",         "ねくたい",
        "ねくら",         "ねこぜ",       "ねこむ",         "ねさげ",
        "ねすごす",       "ねそべる",     "ねだん",         "ねつい",
        "ねっしん",       "ねつぞう",     "ねったいぎょ",   "ねぶそく",
        "ねふだ",         "ねぼう",       "ねほりはほり",   "ねまき",
        "ねまわし",       "ねみみ",       "ねむい",         "ねむたい",
        "ねもと",         "ねらう",       "ねわざ",         "ねんいり",
        "ねんおし",       "ねんかん",     "ねんきん",       "ねんぐ",
        "ねんざ",         "ねんし",       "ねんちゃく",     "ねんど",
        "ねんぴ",         "ねんぶつ",     "ねんまつ",       "ねんりょう",
        "ねんれい",       "のいず",       "のおづま",       "のがす",
        "のきなみ",       "のこぎり",     "のこす",         "のこる",
        "のせる",         "のぞく",       "のぞむ",         "のたまう",
        "のちほど",       "のっく",       "のばす",         "のはら",
        "のべる",         "のぼる",       "のみもの",       "のやま",
        "のらいぬ",       "のらねこ",     "のりもの",       "のりゆき",
        "のれん",         "のんき",       "ばあい",         "はあく",
        "ばあさん",       "ばいか",       "ばいく",         "はいけん",
        "はいご",         "はいしん",     "はいすい",       "はいせん",
        "はいそう",       "はいち",       "ばいばい",       "はいれつ",
        "はえる",         "はおる",       "はかい",         "ばかり",
        "はかる",         "はくしゅ",     "はけん",         "はこぶ",
        "はさみ",         "はさん",       "はしご",         "ばしょ",
        "はしる",         "はせる",       "ぱそこん",       "はそん",
        "はたん",         "はちみつ",     "はつおん",       "はっかく",
        "はづき",         "はっきり",     "はっくつ",       "はっけん",
        "はっこう",       "はっさん",     "はっしん",       "はったつ",
        "はっちゅう",     "はってん",     "はっぴょう",     "はっぽう",
        "はなす",         "はなび",       "はにかむ",       "はぶらし",
        "はみがき",       "はむかう",     "はめつ",         "はやい",
        "はやし",         "はらう",       "はろうぃん",     "はわい",
        "はんい",         "はんえい",     "はんおん",       "はんかく",
        "はんきょう",     "ばんぐみ",     "はんこ",         "はんしゃ",
        "はんすう",       "はんだん",     "ぱんち",         "ぱんつ",
        "はんてい",       "はんとし",     "はんのう",       "はんぱ",
        "はんぶん",       "はんぺん",     "はんぼうき",     "はんめい",
        "はんらん",       "はんろん",     "ひいき",         "ひうん",
        "ひえる",         "ひかく",       "ひかり",         "ひかる",
        "ひかん",         "ひくい",       "ひけつ",         "ひこうき",
        "ひこく",         "ひさい",       "ひさしぶり",     "ひさん",
        "びじゅつかん",   "ひしょ"};
    set_words(words);
    populate_maps();
  }
};
} // namespace Language

#endif
