/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TWISTERX_STATUS_H
#define TWISTERX_STATUS_H
#include "string"
#include "code.cpp"

namespace twisterx {
class Status {

 private:
  int code;
  std::string msg;

 public:

  Status() {

  }

  Status(int code, const std::string &msg) {
	this->code = code;
	this->msg = msg;
  }

  explicit Status(int code) {
	this->code = code;
  }

  explicit Status(Code code) {
	this->code = code;
  }

  Status(Code code, const std::string &msg) {
	this->code = code;
	this->msg = msg;
  }

  int get_code() {
	return this->code;
  }

  bool is_ok() {
	return this->get_code() == Code::OK;
  }

  static Status OK() {
	return twisterx::Status(Code::OK);
  }

  std::string get_msg() {
	return this->msg;
  }
};
}

#endif //TWISTERX_STATUS_H
